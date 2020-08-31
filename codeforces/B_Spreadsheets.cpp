#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define _(x) #x << ": " << to_str(x) << ", "
#define debug(x) { ostringstream stream; stream << x; cout << stream.str() << eol; }
string to_string(basic_string<char>& x) { return "\"" + x + "\""; }
string to_string(char x) { string r = ""; r += x; return "\'" + r + "\'";}
string to_string(bool x) { return x ? "true" : "false"; }
template <typename T> string to_str(T x) { return to_string(x); }
template <typename T1, typename T2> string to_str(pair<T1, T2> x) { return "(" + to_str(x.first) + ", " + to_str(x.second) + ")"; }
template <typename T> string to_str(vector<T> x) { string r = "{"; for (auto t : x) r += to_str(t) + ", "; return r + "}"; }
template <typename T1, typename T2> string to_str(map<T1, T2> x) { string r = "{"; for (auto t : x) r += to_str(t.first) + ": " + to_str(t.second) + ", "; return r + "}"; }
#define ll long long
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    // TODO: Fix this

	unsigned long n, col, row;
    cin >> n;
    string coord;
    for (long unsigned int i = 0; i < n; i++) {
        cin >> coord;
        if (coord[0] == 'R' && isdigit(coord[1]) && coord.find('C') != -1) {
            vector<char> result;
            for (long unsigned int i = 0; i < coord.length(); i++) {
                if (coord[i] == 'R')
                    row = atoi(&coord[i + 1]);
                else if (coord[i] == 'C') {
                    col = atoi(&coord[i + 1]);
                    break;
                }
            }
            bool d = false;
            do {
                if (col % 26 == 0) {
                    if (d)
                        result.push_back('Y');
                    else
                        result.push_back('Z');
                    d = true;
                } else if (d) {
                    d = false;
                    if (col % 26 != 1)
                        result.push_back(char(col % 26 + 63));
                } else
                    result.push_back(char(col % 26 + 64));
                col /= 26;
            } while (col != 0);

            int s = result.size() - 1;
            for (int i = 0; i <= s; i++)
                cout << result[s - i];
            cout << row << eol;
        } else {
        	// debug(_(coord));
            col = int(coord[0]) - 64;
            for (long unsigned int i = 1; i < coord.length(); i++) {
                if (isalpha(coord[i])) {
                    col =  col * 26 + int(coord[i]) - 64;
                } else {
                    row = atoi(&coord[i]);
                    break;
                }
            }
            cout << "R" << row << "C" << col << eol;
            // debug(_(row) << _(col));
        }
    }
    return 0;
}