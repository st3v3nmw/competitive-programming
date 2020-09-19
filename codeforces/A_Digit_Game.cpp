#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define _(x) #x << "=" << to_str(x) << ", "
#define debug(x) { ostringstream stream; stream << x; string s = stream.str(); cout << s.substr(0, s.length() - 2) << eol; }
string to_string(basic_string<char>& x) { return "\"" + x + "\""; }
string to_string(char x) { string r = ""; r += x; return "\'" + r + "\'";}
string to_string(bool x) { return x ? "true" : "false"; }
template <typename T> string to_str(T x) { return to_string(x); }
template <typename T1, typename T2> string to_str(pair<T1, T2> x) { return "(" + to_str(x.first) + ", " + to_str(x.second) + ")"; }
template <typename T> string to_str(vector<T> x) { string r = "{"; for (auto t : x) r += to_str(t) + ", "; return r.substr(0, r.length() - 2) + "}"; }
template <typename T1, typename T2> string to_str(map<T1, T2> x) { string r = "{"; for (auto t : x) r += to_str(t.first) + ": " + to_str(t.second) + ", "; return r.substr(0, r.length() - 2) + "}"; }
#define ll long long
#define ull unsigned ll
const ull MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    unsigned int t, n, c_i;
    char c;
    cin >> t;
    for (unsigned int d = 0; d < t; d++) {
        cin >> n;
        unsigned int epos_even = 0, epos_odd = 0, opos_even = 0, opos_odd = 0;
        for (unsigned int i = 1; i <= n; i++) {
            cin >> c;
            c_i = c - 48;
            if (n == 1) {
                if (c_i % 2 == 0) {
                    cout << 2 << endl;
                } else
                    cout << 1 << endl;
                goto end;
            }

            if (i % 2 == 0) {
                if (c_i % 2 == 0) {
                    epos_even++;
                } else {
                    epos_odd++;
                }
            } else {
                if (c_i % 2 == 0) {
                    opos_even++;
                } else {
                    opos_odd++;
                }
            }
        }

        // raze -> odd, breach -> even
        unsigned int ch, n2;
        if (n % 2 == 0) {
            if (epos_even > 0) {
                cout << 2 << endl;
            } else {
                cout << 1 << endl;
            }
        } else {
            if (opos_odd > 0) {
                cout << 1 << endl;
            } else {
                cout << 2 << endl;
            }
        }
        // debug(_(epos_even) << _(epos_odd) << _(opos_even) << _(opos_odd));
        end:
            continue;
    }
}