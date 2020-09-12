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
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int t, n, c1 = 0, c2 = 0, c3 = 0, taxis = 0;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        switch(n) {
            case 1:
                c1++;
                break;
            case 2:
                c2++;
                break;
            case 3:
                c3++;
                break;
            default:
                taxis++;
        }
    }

    int d = min(c1, c3);
    taxis += d;
    c1 -= d;
    c3 -= d;
    taxis += c3;
    d = c2 / 2;
    taxis += d;
    c2 -= 2 * d;
    d = min(c2, c1 / 2);
    taxis += d;
    c2 -= d;
    c1 -= 2 * d;
    d = c2 != 0 && c1 > 0;
    taxis += d;
    c1 -= d;
    c2 -= d;
    taxis += c2;
    d = c1 / 4;
    taxis += d;
    c1 -= 4 * d;
    taxis += c1 > 0;

    cout << taxis << endl;
}