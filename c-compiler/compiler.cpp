#include <iostream>
#include <fstream>
#include <memory>
#include <cstring>
#include <map>
#include <sys/wait.h>
#include <unistd.h>

#define IDENT_LIM 256 // limit on identifier length
#define IDENT_BUFFER_LEN IDENT_LIM + 1

using namespace std;

// list of printable tokens
string tokstr[] = {"+", "-", "*", "/", "==", "!=", "<", ">", "<=", ">=", "intlit", ";", "=", "identifier", "print", "int"};

// Tokens
enum {
  T_EOF,
  T_PLUS, T_MINUS,  // additive operators
  T_STAR, T_SLASH,  // multiplicative operators
  T_EQ, T_NEQ,       // ==, !=
  T_LT, T_GT, T_LE, T_GE, // <, >, <=, >=
  T_INTLIT, T_SEMI, T_ASSIGN, T_IDENT,
  T_PRINT, T_INT // keywords
};

// operator precedence for each token
static int opPrec[] = {
    0, 1, 1,    // T_EOF, T_PLUS, T_MINUS
    2, 2,       // T_STAR, T_SLASH
    3, 3,       // T_EQ, T_NEQ
    4, 4, 4, 4  // T_LT, T_GT, T_LE, T_GE
};

class Token {
    public:
        Token() {}

        void setToken(int token) {
            Token::token = token;
        }

        void setValue(int value) {
            Token::value = value;
        }

        int getToken() {
            return token;
        }

        int getValue() {
            return value;
        }
    
    private:
        int token, value;
};

// AST node types
enum {
  A_ADD=1, A_SUBTRACT, A_MULTIPLY, A_DIVIDE,
  A_EQ, A_NEQ, A_LT, A_GT, A_LE, A_GE,
  A_INTLIT,
  A_IDENT, A_LVIDENT, A_ASSIGN
};

// Abstract Syntax Tree node
class ASTNode {
    public:
        ASTNode(int op, int value) { // node without subtrees
            init(op, value);
            left = NULL;
            right = NULL;
        }

        ASTNode(int op, int value, shared_ptr<ASTNode> left_node, shared_ptr<ASTNode> right_node) {
            init(op, value);
            left = left_node;
            right = right_node;
        }

        void traverse() {
            // print in preorder (prefix notation)
            if (op == A_INTLIT)
                cout << value << " ";
            else
                cout << tokstr[op] << " ";

            if (left)
                left->traverse();

            if (right)
                right->traverse();
        }

    private:
        int op; // operation to be performed
        int value; // For A_INTLIT's integer value or for A_IDENT the symbol slot
        shared_ptr<ASTNode> left, right; // these f[a-z]*ing pointers :(

        void init(int op, int value) {
            ASTNode::op = op;
            ASTNode::value = value;
        }

    friend class Compiler;
};


class Compiler {
    public:
        Compiler(string path) {
            // read file
            inputPath = path;
            ifstream inputFl(path, ios::in);
            if (!inputFl) {
                cerr << "Unable to open " << path << endl;
                exit(1);
            }
            inputFile.swap(inputFl);

            // get the cleaned up filename
            int name_start = path.find_last_of('/');
            int name_end = path.find_last_of('.');
            filename = path.substr(name_start != -1 ? name_start + 1: 0, name_end != -1 ? name_end : path.length());

            // assembly output file
            outputPath = "./out/" + filename + ".s";
            ofstream outputFl(outputPath, ios::out);
            if (!outputFl) {
                cerr << "Couldn't create out file" << endl;
                exit(1);
            }
            outputFile.swap(outputFl);

            // output preamble
            cg_preamble();

            // parse and generate assembly code
            token = Token();
            scanChars(); // get the 1st token
            parse(); // parse the statements
            cout << filename << " parsed successfully :)" << endl;

            // output postamble
            cg_postamble();
        }


        /* scanning and parsing */
    
        void parse() {
            while (1) {
                switch (token.getToken()) {
                    case T_PRINT:
                        print_statement();
                        break;
                    case T_INT:
                        var_declaration();
                        break;
                    case T_IDENT:
                        assignment_statement();
                        break;
                    case T_EOF:
                        return;
                    default:
                        error_exit("Syntax error, token", token.getToken());
                }
            }
        }

        // handle a print statement
        void print_statement() {
            int reg;
            // match a 'print' as the first token
            match(T_PRINT, "print");

            // parse the expression & generate the assembly code
            root = binexpr(0);
            reg = genASM(root, -1);
            cg_printint(reg);
            free_all_registers();
            semi();
        }

        // handle a declaration statement
        void var_declaration() {
            // int then identifier then semicolon ;
            match(T_INT, "int");
            ident();
            string name(buf);
            addglob(name);
            cg_globsym();
            semi();
        }

        // handle an assignment statement
        void assignment_statement() {
            shared_ptr<ASTNode> left;
            int id;

            // ensure we have an identifier
            ident();

            // check if it's been defined then make a leaf node for it
            string name(buf);
            if ((id = findglob(name)) == -1)
                error_exit("Undeclared variable", name);

            shared_ptr<ASTNode> right(new ASTNode(A_LVIDENT, id));

            // ensure we have an assignment operator
            match(T_ASSIGN, "=");

            // parse the following expressino
            left = binexpr(0);

            // make an assignment AST tree
            shared_ptr<ASTNode> tree(new ASTNode(A_ASSIGN, 0, left, right));

            // generate the assembly code
            genASM(tree, -1);
            free_all_registers();

            // match the semicolon
            semi();
        }

        // ensure that the current token is t and fetch the next token
        // else throw an error
        void match(int t, string what) {
            if (token.getToken() == t) {
                scanChars();
            } else {
                error_exit(what, "expected on line");
            }
        }

        // match a semicolon
        inline void semi() {
            match(T_SEMI, ";");
        }

        // match an identifier
        inline void ident() {
            match(T_IDENT, "identifier");
        }

        // return an AST tree whose root is a binary operator
        // Parameter ptp is the previous token's precedence
        shared_ptr<ASTNode> binexpr(int ptp) {
            shared_ptr<ASTNode> left, right;
            left = primary(); // build the left sub-tree

            int tokenType = token.getToken();
            // base case, no tokens left
            if (tokenType == T_SEMI) // statements terminated by a semicolon
                return left;

            // while the precedence of this token
            // is more than that of the previous token precedence
            while (opPrecedence(tokenType) > ptp) {
                scanChars();

                // recursively call parse with the precedence
                // of our token to build a sub-tree
                right = binexpr(opPrec[tokenType]);

                // join the right sub-tree above with the tree we already have
                shared_ptr<ASTNode> left2(new ASTNode(arithOp(tokenType), 0, left, right));
                left = left2;

                tokenType = token.getToken();
                if (tokenType == T_SEMI) // statements terminated by a semicolon
                    break;
            }

            return left;
        }

        // return a node with a number (T_INTLIT)
        shared_ptr<ASTNode> primary() {
            switch (token.getToken()) {
                case T_INTLIT:
                    {
                        shared_ptr<ASTNode> node(new ASTNode(A_INTLIT, token.getValue()));
                        scanChars();
                        return node; 
                    }
                case T_IDENT:
                    {
                        // check that this identifier exists
                        string name(buf);
                        int id = findglob(name);
                        if (id == -1) {
                            error_exit("Unknown variable", name);
                        }
                        shared_ptr<ASTNode> node(new ASTNode(A_IDENT, id));
                        scanChars();
                        return node;
                    }
                default:
                    printf("Syntax error on line %d:%d\n", n_line, line_pos);
                    exit(1);
            }
        }

        int scanChars() {
            if (!skip()) { // read the next character, skip whitespace
                token.setToken(T_EOF);
                return 0; // EOF
            }

            switch (c) { // determine token type
                case '+':
                    token.setToken(T_PLUS);
                    break;
                case '-':
                    token.setToken(T_MINUS);
                    break;
                case '*':
                    token.setToken(T_STAR);
                    break;
                case '/':
                    token.setToken(T_SLASH);
                    break;
                case ';':
                    token.setToken(T_SEMI);
                    break;
                case '=':
                    next();
                    if (c == '=') // ==
                        token.setToken(T_EQ);
                    else {
                        inputFile.putback(c);
                        token.setToken(T_ASSIGN);
                    }
                    break;
                case '!':
                    next();
                    if (c == '=')
                        token.setToken(T_NEQ);
                    else
                        error_exit("Unrecognized character", c);
                    break;
                case '<':
                    next();
                    if (c == '=')
                        token.setToken(T_LE);
                    else {
                        inputFile.putback(c);
                        token.setToken(T_LT);
                    }
                    break;
                case '>':
                    next();
                    if (c == '=')
                        token.setToken(T_GE);
                    else {
                        inputFile.putback(c);
                        token.setToken(T_GT);
                    }
                    break;
                default:
                    if (isdigit(c)) {
                        token.setValue(scanint()); // if it's a digit, scan the literal integer value
                        token.setToken(T_INTLIT);
                        break;
                    } else if (isalpha(c) || '_' == c) {
                        // scan keyword or identifier
                        scanident();

                        // if it's a recognized keyword, return token
                        int tokenType = keyword();
                        if (tokenType) {
                            token.setToken(tokenType);
                            break;
                        }

                        // not a recognized keyword, so it must be an identifier
                        token.setToken(T_IDENT);
                        break;
                    }

                    error_exit("Unrecognized character", c);
            }
            return 1; // we found a token
        }

        // scan an integer
        int scanint() {
            int val = 0;
            while(isdigit(c)) {
                val = val * 10 + c - 48; // offset by 48 to convert ASCII to integer
                next();
            }

            inputFile.putback(c); // put back a non-int character
            line_pos--; // decrement our line position when we put back a character
            return val;
        }

        // scan an identifier
        int scanident() {
            int i = 0;
            // allow alphanumeric & underscores
            while (isalnum(c) || '_' == c) {
                // error if we reach the identifier length limit,
                // else append to buf and get next char
                if (ident_lim - 1 == i) {
                    error_exit("Identifier too long on", "");
                };
                buf[i++] = c;
                next();
            }

            buf[i] = '\0'; // null terminate buf
            // put back a non-valid char
            inputFile.putback(c);
            line_pos--;
            return i; // length of identifier
        }

        // given a word in the buffer buf, return the matching keyword
        // token number or 0 if it's not a keyword
        int keyword() {
            switch(buf[0]) {
                case 'p':
                    if (!strcmp(buf, "print"))
                        return T_PRINT;
                    break;
                case 'i':
                    if (!strcmp(buf, "int"))
                        return T_INT;
                    break;
            }
            return 0;
        }

        // get the next character
        int next() {
            if (!(inputFile >> noskipws >> c))
                    return 0; // EOF
            if (c == '\n') {
                n_line++;
                line_pos = 0; // reset out position on the line
            }

            line_pos++; // increment our position on the current line
            return 1; // we found a char
        }

        // skip whitespace
        int skip() {
            c = ' ';
            while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
                if(!next())
                    return 0; // EOF
            }
            return 1;
        }

        // convert a token into an AST operation
        // 1:1 mapping
        int arithOp(int tokenType) {
            if (tokenType > T_EOF && tokenType < T_INTLIT)
                return tokenType;
            error_exit("Unknown token", tokstr[tokenType]);
            return -1; // unreachable code
        }

        // return a tokenType's precedence
        int opPrecedence(int tokenType) {
            int prec = opPrec[tokenType];
            if (prec == 0) {
                error_exit("Syntax error, token", tokenType);
            }
            return prec;
        }


        /* code generation */

        // given an AST, generate assembly code recursively
        int genASM(shared_ptr<ASTNode> node, int reg) {
            // int leftval = 0, rightval = 0;
            int leftreg, rightreg;

            // get the values of the left and right subtrees
            if (node->left)  leftreg  = genASM(node->left, -1);
            if (node->right) rightreg = genASM(node->right, leftreg);

            switch (node->op) {
                case A_ADD:      return cg_add(leftreg, rightreg);
                case A_SUBTRACT: return cg_sub(leftreg, rightreg);
                case A_MULTIPLY: return cg_mul(leftreg, rightreg);
                case A_DIVIDE:   return cg_div(leftreg, rightreg);
                case A_INTLIT:   return cg_load(node->value);
                case A_IDENT:    return cg_load_glob(Gsym[node->value]);
                case A_LVIDENT:  return cg_store_glob(reg, Gsym[node->value]);
                case A_ASSIGN:   return rightreg; // the work has already been done
                case A_EQ:       return cg_equal(leftreg, rightreg);
                case A_NEQ:      return cg_not_equal(leftreg, rightreg);
                case A_LT:       return cg_less_than(leftreg, rightreg);
                case A_GT:       return cg_greater_than(leftreg, rightreg);
                case A_LE:       return cg_less_equal(leftreg, rightreg);
                case A_GE:       return cg_greater_equal(leftreg, rightreg);
                default:
                    printf("Unknown AST operator %d\n", node->op);
                    exit(1);
            }
        }

        // add a global symbol to the symbol table
        inline int addglob(string name) {
            int y;
            // if symbol's already in symbol table
            if ((y = findglob(name)) != -1) {
                // return y;
                error_exit("Redeclaration of", name);
            }
            // otherwise, get a new slot
            y = n_globs++;
            Gsym[y] = name;
            return y;
        }

        // find if a glob exists
        inline int findglob(string name) {
            for (auto it = Gsym.begin(); it != Gsym.end(); ++it) {
                if (it->second == name)
                    return it->first;
            }
            return -1;
        }

        // allocate a ree register
        int alloc_register() {
            for (int i = 0; i < 4; i++) {
                if (freereg[i]) {
                    freereg[i] = 0;
                    return i;
                }
            }
            cerr << "Out of registers :(" << endl;
            exit(1);
        }

        // free a register
        void free_register(int reg) {
            if (freereg[reg] != 0) {
                error_exit("Error trying to free register", reg);
            }
            freereg[reg] = 1;
        }

        // free all registers
        void free_all_registers() {
            freereg[0] = freereg[1] = freereg[2] = freereg[3] = 1;
        }

        // Print out the assembly preamble
        void cg_preamble() {
            outputFile <<   "\t.text\n"
                            ".LC0:\n"
                            "\t.string\t\"%d\\n\"\n"
                            "printint:\n"
                            "\tpushq\t%rbp\n"
                            "\tmovq\t%rsp, %rbp\n"
                            "\tsubq\t$16, %rsp\n"
                            "\tmovl\t%edi, -4(%rbp)\n"
                            "\tmovl\t-4(%rbp), %eax\n"
                            "\tmovl\t%eax, %esi\n"
                            "\tleaq	.LC0(%rip), %rdi\n"
                            "\tmovl	$0, %eax\n"
                            "\tcall	printf@PLT\n"
                            "\tnop\n"
                            "\tleave\n"
                            "\tret\n"
                            "\n"
                            "\t.globl\tmain\n"
                            "\t.type\tmain, @function\n"
                            "main:\n"
                            "\tpushq\t%rbp\n"
                            "\tmovq	%rsp, %rbp\n";
        }

        // Print out the assembly postamble
        void cg_postamble() {
            outputFile << 	"\tmovl	$0, %eax\n"
	                        "\tpopq	%rbp\n"
	                        "\tret\n";
        }

        int cg_add(int r1, int r2) {
            outputFile << "\taddq\t" << reglist[r1] << ", " << reglist[r2] << "\n";
            free_register(r1);
            return r2;
        }

        int cg_sub(int r1, int r2) {
            outputFile << "\tsubq\t" << reglist[r2] << ", " << reglist[r1] << "\n";
            free_register(r2);
            return r1;
        }

        int cg_mul(int r1, int r2) {
            outputFile << "\timulq\t" << reglist[r1] << ", " << reglist[r2] << "\n";
            free_register(r1);
            return r2;
        }

        int cg_div(int r1, int r2) {
            outputFile << "\tmovq\t" << reglist[r1] << ", %rax\n";
            outputFile << "\tcqo\n";
            outputFile << "\tidivq\t" << reglist[r2] << "\n";
            outputFile << "\tmovq\t%rax, " << reglist[r1] << "\n";
            free_register(r2);
            return r1;
        }

        // load an integer literal value into a register
        int cg_load(int value) {
            int r = alloc_register(); // allocate a free register
            outputFile << "\tmovq\t$" << value << ", " << reglist[r] << "\n";
            return r;
        }

        // load a value from a variable into a register
        int cg_load_glob(string identifier) {
            int r = alloc_register();
            outputFile << "\tmovq\t" << identifier << "(\%rip), " << reglist[r] << "\n";
            return r;
        }

        // store a register's value into a register
        int cg_store_glob(int r, string identifier) {
            outputFile << "\tmovq\t" << reglist[r] << ", " << identifier << "(\%rip)\n";
            return r;
        }

        // call printint with a certain register
        void cg_printint(int r) {
            outputFile << "\tmovq\t" << reglist[r] << ", %rdi\n";
            outputFile << "\tcall\tprintint\n";
            free_register(r);
        }

        // generate a global symbol
        void cg_globsym() {
            string name(buf);
            outputFile << "\t.comm\t" << name << ",8,8\n";
        }

        // compare two registers
        int cg_compare(int r1, int r2, string how) {
            outputFile << "\tcmpq\t" << reglist[r2] << ", " << reglist[r1] << "\n";
            outputFile << "\t" << how << "\t" << breglist[r2] << "\n";
            outputFile << "\tandq\t$255," << reglist[r2] << "\n";
            free_register(r1);
            return r2;
        }

        int cg_equal(int r1, int r2) { return cg_compare(r1, r2, "sete");}
        int cg_not_equal(int r1, int r2) { return cg_compare(r1, r2, "setne");}
        int cg_less_than(int r1, int r2) { return cg_compare(r1, r2, "setl");}
        int cg_greater_than(int r1, int r2) { return cg_compare(r1, r2, "setg");}
        int cg_less_equal(int r1, int r2) { return cg_compare(r1, r2, "setle");
        }
        int cg_greater_equal(int r1, int r2) { return cg_compare(r1, r2, "setge");}


        /* debugging */

        void traverseAST() {
            root->traverse();
            cout << endl;
        }

        template <typename T>
        inline void error_exit(string err_msg, T extra) {
            cerr << err_msg << " " << extra << " on line " << n_line << ":" << line_pos << endl;

            // print the backtrace using gdb
            char pid_buf[32];
            sprintf(pid_buf, "%d", getpid());
            char name_buf[512];
            name_buf[readlink("/proc/self/exe", name_buf, 511)] = 0;
            int child_pid = fork();
            if (!child_pid) {
                dup2(2, 1); // redirect output to stderr
                fprintf(stdout, "\nStack trace for %s pid=%s\n", name_buf, pid_buf);
                execlp("gdb", "gdb", "--batch", "-n", "-ex", "thread", "-ex", "bt", name_buf, pid_buf, NULL);
                abort(); // if gdb failed to start
            } else {
                waitpid(child_pid, NULL, 0);
            }

            // delete created ASM output file
            int len = outputPath.length();
            char outputPath2[len + 1];
            for (int i = 0; i < len; i++) {
                outputPath2[i] = outputPath[i];
            }

            outputPath2[len] = '\0';
            remove(outputPath2);
            exit(1);
        }

        void print_symbol_table() {
            for (auto it = Gsym.begin(); it != Gsym.end(); ++it)
                cout << it->first << " " << it->second << "\n";
        }
    
    private:
        // parsing & scanning stuff
        char c;
        int n_line = 1, line_pos = 0, ident_lim = IDENT_LIM;
        ifstream inputFile;
        string inputPath, filename;
        shared_ptr<ASTNode> root;
        Token token;
        char buf[IDENT_BUFFER_LEN];

        // code generation stuff
        ofstream outputFile;
        string outputPath;
        int freereg[4] = {1, 1, 1, 1};
        int n_globs = 0; // number of globals
        const string reglist[4] = {"%r8", "%r9", "%r10", "%r11"};
        const string breglist[4] = { "%r8b", "%r9b", "%r10b", "%r11b" };
        map<int, string> Gsym; // store global variables
};

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " infile\n";
        exit(1);
    }

    Compiler compiler(argv[1]) ;
    // compiler.print_symbol_table();
    // compiler.traverseAST();
    // compiler.generateAssembly();

    return 0;
}