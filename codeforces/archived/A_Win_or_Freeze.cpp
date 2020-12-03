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
    // ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ull q;
    cin >> q;
    vector<ull> divisors;
    ull upper = sqrt(q);
    for (int d = 2; d <= upper; d++) {
        if (q % d == 0)
            divisors.push_back(d);
        if (divisors.size() == 2)
            break;
    }

    if (divisors.size() == 0) // prime or 1
        cout << 1 << eol << 0 << eol;
    else if (divisors.size() == 1 || divisors[0] * divisors[1] == q) {
        double x = log(q) / log(divisors[0]);
        if (floor(x) == x) {
            ull x2 = floor(x);
            if (x2 & 1) {
                cout << 1 << eol;
                cout << divisors[0] * divisors[0] << eol;
            } else {
                cout << 2 << eol;
            }
        } else {
            cout << 2 << eol;
        }
    } else  {
        ull p = divisors[0];
        cout << 1 << eol;
        cout << (p * p == divisors[1] ? divisors[1] : p * divisors[1]) << eol;
    }
}