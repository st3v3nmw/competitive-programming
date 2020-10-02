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
    
    int g, n;
    cin >> g;
    for (int t = 0; t < g; t++) {
        ll total = 0, sub = 0;
        cin >> n;
        vector<ll> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            total += v[i];
        }
        int s = 0;
        for (int i = 0; i < n - 1; i++) {
            if (v[i] + sub <= 0) {
                sub = 0;
                s = i + 1;
            } else
                sub += v[i];
            if (sub >= total) {
                cout << "NO\n";
                goto end;
            }
        }
        if (s == 0 && sub > 0) {
            sub = max(sub, v[n - 1]);
            cout << (sub >= total ? "NO\n" : "YES\n");
            continue;
        }
        if (v[n - 1] > 0)
            sub += v[n - 1];
        cout << (sub >= total ? "NO\n" : "YES\n");
        end:
            continue;
    }
}