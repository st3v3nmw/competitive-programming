#include <iostream>
#include <fstream>

using namespace std;

// list of printable tokens
string tokstr[] = {"+", "-", "*", "/", "intlit"};

// Tokens
enum {
  T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT
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

class FileScanner {
    public:
        FileScanner(string filename) {
            FileScanner::filename = filename;
            ifstream inputFl(filename, ios::in);
            if (!inputFl) {
                cerr << "Unable to open " << filename << endl;
                exit(1);
            }
            inputFile.swap(inputFl);
            n_line = 1, line_pos = 0;
        }

        void scan() { // scan all tokens of the input file
            Token t;
            while (scanChars(&t)) {
                cout << "Token " << tokstr[t.getToken()];
                if (t.getToken() == T_INTLIT)
                    cout << ", value " << t.getValue();
                cout << "\n";
            }
        }

        int scanChars(Token* t) {
            if (!next()) // read the next character
                return 0; // EOF

            switch (c) { // determine token type
                case '+':
                    t->setToken(T_PLUS);
                    break;
                case '-':
                    t->setToken(T_MINUS);
                    break;
                case '*':
                    t->setToken(T_STAR);
                    break;
                case '/':
                    t->setToken(T_SLASH);
                    break;
                default:
                    if (isdigit(c)) {
                        t->setValue(scanint()); // if it's a digit, scan the literal integer value
                        t->setToken(T_INTLIT);
                        break;
                    }

                    printf("Unrecognized character %c on line %d:%d\n", c, n_line, line_pos);
                    exit(1);
            }
            return 1; // we found a token
        }

        int scanint() {
            int val = c - 48; // offset by 48 to convert ASCII to integer
            while(isdigit(c)) {
                val = val * 10 + c - 48;
                next();
            }

            inputFile.putback(c); // put back extra character
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
    
    private:
        char c;
        int n_line, line_pos;
        ifstream inputFile;
        string filename;
};


int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " infile\n";
        exit(1);
    }

    FileScanner scanner(argv[1]);
    scanner.scan();

    return 0;
}