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
    
    int n, h, d = 2, p = 1;
    cin >> n >> h;
    int g = n, k = h;
    vector<int> b;
    k--;
    int upper = sqrt(n) + 1;
    while (k-- && d < upper) {
        if (p == n)
            break;
        if (g % d == 0) {
            g /= d;
            b.push_back(d);
            p *= d;
        } else {
            d++;
            k++;
        }
    }
    if (p != n)
        b.push_back(n / p);
    if (b.size() != h)
        cout << -1 << eol;
    else {
        for (int e : b)
            cout << e << " ";
        cout << eol;
    }
}