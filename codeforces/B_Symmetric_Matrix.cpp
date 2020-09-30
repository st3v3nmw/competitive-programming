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
    int n, m, x1, x2, x3, x4;
    for (int t = 0; t < g; t++) {
        cin >> n >> m;
        vector<vector<int>> v;
        bool f = false, f2 = false, f3 = false;
        for (int i = 0; i < n; i++) {
            vector<int> q(4);
            cin >> q[0] >> q[1] >> q[2] >> q[3];
            if (q[1] == q[2])
                f = true;
            if (q[0] == q[3] && q[1] == q[2])
                f3 = true;
               
            v.push_back(q);
        }
        if (m & 1)
            cout << "NO\n";
        else {
            // debug(_(v));
            for (int i = 0; i < v.size(); i++) {
                for (int j = i; j < v.size(); j++) {
                    if (v[i][0] == v[j][3]) {
                        f2 = true;
                        goto end;
                    }
                }
            }
            end:
            cout << ((f && f2 && f3) ? "YES\n" : "NO\n");
        }
    }
}