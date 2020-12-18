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
    
    int g;
    cin >> g;
    for (int t = 0; t < g; t++) {
        int n;
        cin >> n;
        stack<char> s;
        char c, f;
        int cnt = 0, q = 0;
        for (int i = 0; i < n; i++) {
            cin >> c;
            if (s.size() == 0) {
                s.push(c);
                f = c;
            } else if (i == n - 1 && f == '>' && f != c) {
                s.push(c);
            } else if (s.top() == '>' && c == '<' || s.top() == '<' && c == '>') {
                s = stack<char>();
                s.push(c);
            } else {
                s.push(c);
                q += c == '-';
            }
        }
        if (q == 0) {
            cout << (s.size() == n ? n : 0) << eol;
        } else {
            
            cout << (s.size() == n ? n : s.size() + q) << eol;
        }
    }
}