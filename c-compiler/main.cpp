#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

// list of printable tokens
string tokstr[] = {"+", "-", "*", "/", "intlit"};

// Tokens
enum {
  T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_EOF
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

        ASTNode(int op, int value, shared_ptr<ASTNode> left_node) {
            init(op, value);
            left = left_node;
            right = NULL;
        }

        void traverse() {
            // print in preorder
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

    friend class Parser;
};


class Parser {
    public:
        Parser(string filename) {
            Parser::filename = filename;
            ifstream inputFl(filename, ios::in);
            if (!inputFl) {
                cerr << "Unable to open " << filename << endl;
                exit(1);
            }
            inputFile.swap(inputFl);
            n_line = 1, line_pos = 0;
            token = Token();
            scanChars();
            root = parse();
        }

        shared_ptr<ASTNode> parse() { // scan & parse all tokens of the input file
            shared_ptr<ASTNode> left = primary();

            // base case, not tokens left
            if (token.getToken() == T_EOF)
                return left;

            int nodeType = arithOp(token.getToken());

            scanChars(); // get next token

            shared_ptr<ASTNode> right = parse(); // get right subtree

            // build & return a complete AST node
            shared_ptr<ASTNode> result(new ASTNode(nodeType, 0, left, right));
            return result;
        }

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

        // evaluate the AST and return a final value
        int interpretAST() {
            return evaluateAST(root);
        }

        int scanChars() {
            if (!next()) { // read the next character
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
                default:
                    if (isdigit(c)) {
                        token.setValue(scanint()); // if it's a digit, scan the literal integer value
                        token.setToken(T_INTLIT);
                        break;
                    }

                    printf("Unrecognized character %c on line %d:%d\n", c, n_line, line_pos);
                    exit(1);
            }
            return 1; // we found a token
        }

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

        int next() { // return the next character
            c = ' ';
            while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) { // skip whitespace
                if (c == '\n') {
                    n_line++;
                    line_pos = 0; // reset our position on the line
                }
                if (!(inputFile >> noskipws >> c))
                    return 0;
                line_pos++; // increment our position on the current line
            }
            return 1;
        }

        // convert a token into an AST operation
        int arithOp(int tok) {
            switch (tok) {
                case T_PLUS:
                    return A_ADD;
                case T_MINUS:
                    return A_SUBTRACT;
                case T_STAR:
                    return A_MULTIPLY;
                case T_SLASH:
                    return A_DIVIDE;
                default:
                    printf("Unknown token %d in arithop() on line %d\n", tok, n_line);
                    exit(1);
            }
        }

        void traverseAST() {
            root->traverse();
            cout << endl;
        }
    
    private:
        char c;
        int n_line, line_pos;
        ifstream inputFile;
        string filename;
        shared_ptr<ASTNode> root;
        Token token;

        int evaluateAST(shared_ptr<ASTNode> node) {
            int leftval = 0, rightval = 0;

            // get the values of the left and right subtrees
            if (node->left)
                leftval = evaluateAST(node->left);
            if (node->right)
                rightval = evaluateAST(node->right);

            if (node->op == A_INTLIT)
                cout << node->value << endl;
            else
                cout << leftval << tokstr[node->op] << rightval << endl;

            // refactor this using functional code
            switch (node->op) {
                case A_ADD:
                    return leftval + rightval;
                case A_SUBTRACT:
                    return leftval - rightval;
                case A_MULTIPLY:
                    return leftval * rightval;
                case A_DIVIDE:
                    return leftval / rightval;
                case A_INTLIT:
                    return node->value;
                default:
                    printf("Unknown AST operator %d\n", node->op);
                    exit(1);
            }
        }
};

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " infile\n";
        exit(1);
    }

    Parser parser(argv[1]);
    parser.traverseAST();
    cout << parser.interpretAST() << endl;

    return 0;
}