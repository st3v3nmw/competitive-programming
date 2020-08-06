#include <iostream>
#include <fstream>
#include <memory>
#include <cstring>

#define IDENT_LIM 256 // limit on identifier length
#define IDENT_BUFFER_LEN IDENT_LIM + 1

using namespace std;

// list of printable tokens
string tokstr[] = {"+", "-", "*", "/", "intlit"};

// Tokens
enum {
  T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_PRINT, T_SEMI
};

// operator precedence for each token
static int opPrec[] = {0, 1, 1, 2, 2, 0}; // EOF, +, -, *, /, INT_LIT

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
  A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT
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
        int value; // For A_INTLIT's integer value
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
            asm_preamble();

            // parse and generate assembly code
            token = Token();
            scanChars();
            parse();
            cout << filename << " parsed successfully :)" << endl;

            // output postamble
            asm_postamble();
        }


        /* scanning and parsing */
    
        void parse() {
            int reg;
            while (1) {
                // match a 'print' as the first token
                match(T_PRINT, "print");

                // parse the expression & generate the assembly code
                root = binexpr(0);
                reg = genASM(root);
                asm_printint(reg);
                free_all_registers();
                
                // match the following semicolon
                // stop of we're at EOF
                match(T_SEMI, ";");
                if (token.getToken() == T_EOF)
                    return;
            }
        }

        // ensure that the current token is t and fetch the next token
        // else throw an error
        void match(int t, string what) {
            if (token.getToken() == t) {
                scanChars();
            } else {
                cout << what << " expected on line " << n_line << endl;
                error_exit();
            }
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

                        // not a recognized keyword
                        printf("Unrecognized symbol %s on line %d\n", buf, n_line);
                        error_exit();
                    }

                    printf("Unrecognized character %c on line %d:%d\n", c, n_line, line_pos);
                    error_exit();
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
                    printf("Identifier too long on line %d\n", n_line);
                    error_exit();
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
        int arithOp(int tok) {
            switch (tok) {
                case T_PLUS:  return A_ADD;
                case T_MINUS: return A_SUBTRACT;
                case T_STAR:  return A_MULTIPLY;
                case T_SLASH: return A_DIVIDE;
                default:
                    printf("Unknown token %d in arithop() on line %d\n", tok, n_line);
                    exit(1);
            }
        }

        // return a tokenType's precedence
        int opPrecedence(int tokenType) {
            int prec = opPrec[tokenType];
            if (prec == 0) {
                printf("Syntax error on line %d:%d, token %d\n", n_line, line_pos, tokenType);
                error_exit();
            }
            return prec;
        }


        /* code generation */

        // given an AST, generate assembly code recursively
        int genASM(shared_ptr<ASTNode> node) {
            // int leftval = 0, rightval = 0;
            int leftreg, rightreg;

            // get the values of the left and right subtrees
            if (node->left)  leftreg  = genASM(node->left);
            if (node->right) rightreg = genASM(node->right);

            switch (node->op) {
                case A_ADD:      return asm_add(leftreg, rightreg);
                case A_SUBTRACT: return asm_sub(leftreg, rightreg);
                case A_MULTIPLY: return asm_mul(leftreg, rightreg);
                case A_DIVIDE:   return asm_div(leftreg, rightreg);
                case A_INTLIT:   return asm_load(node->value);
                default:
                    printf("Unknown AST operator %d\n", node->op);
                    exit(1);
            }
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
                cerr << "Error trying to free register " << reg << endl;
                error_exit();
            }
            freereg[reg] = 1;
        }

        // free all registers
        void free_all_registers() {
            freereg[0] = freereg[1] = freereg[2] = freereg[3] = 1;
        }

        // Print out the assembly preamble
        void asm_preamble() {
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
        void asm_postamble() {
            outputFile << 	"\tmovl	$0, %eax\n"
	                        "\tpopq	%rbp\n"
	                        "\tret\n";
        }

        int asm_add(int r1, int r2) {
            outputFile << "\taddq\t" << reglist[r1] << ", " << reglist[r2] << "\n";
            free_register(r1);
            return r2;
        }

        int asm_sub(int r1, int r2) {
            outputFile << "\tsubq\t" << reglist[r2] << ", " << reglist[r1] << "\n";
            free_register(r2);
            return r1;
        }

        int asm_mul(int r1, int r2) {
            outputFile << "\timulq\t" << reglist[r1] << ", " << reglist[r2] << "\n";
            free_register(r1);
            return r2;
        }

        int asm_div(int r1, int r2) {
            outputFile << "\tmovq\t" << reglist[r1] << ", %rax\n";
            outputFile << "\tcqo\n";
            outputFile << "\tidivq\t" << reglist[r2] << "\n";
            outputFile << "\tmovq\t%rax, " << reglist[r1] << "\n";
            free_register(r2);
            return r1;
        }

        int asm_load(int value) {
            int r = alloc_register(); // allocate a free register
            outputFile << "\tmovq\t$" << value << ", " << reglist[r] << "\n";
            return r;
        }

        // call printint with a certain register
        void asm_printint(int r) {
            outputFile << "\tmovq\t" << reglist[r] << ", %rdi\n";
            outputFile << "\tcall\tprintint\n";
            free_register(r);
        }


        /* debugging */

        void traverseAST() {
            root->traverse();
            cout << endl;
        }

        inline void error_exit() {
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
        string reglist[4] = {"%r8", "%r9", "%r10", "%r11"};
};

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " infile\n";
        exit(1);
    }

    Compiler compiler(argv[1]);
    // compiler.traverseAST();
    // compiler.generateAssembly();

    return 0;
}