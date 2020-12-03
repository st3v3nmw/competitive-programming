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
    
    ll g, m, n, c;
    cin >> g;
    for (int t = 0; t < g; t++) {
        cin >> n >> m;
        c = 0;
        vector<int> v(n * m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                cin >> v[i * m + j];
        }

        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < m / 2; j++) {
                int q = v[i * m + j], w = v[i * m + m - j - 1];
                int e = v[(n - i - 1) * m + j], r= v[(n - i - 1) * m + m - j - 1];
                int t = (q + w + e + r) / 4;
                c += abs(t - q) + abs(t - w) + abs(t - r) + abs(t - e);
            }
        }

        if (n & 1 && n != 1) {
            int t = 0;
            for (int j = 0; j < m; j++)
                t += v[n / 2 * m + j];
            
            if (m & 1) {
                t -= v[n / 2 * m + m / 2];
                t /= (m - 1);
                for (int j = 0; j < m; j++)
                    c += abs(t - v[n / 2 * m + j]);
                c -= abs(t - v[n / 2 * m + m / 2]);
            } else {
                t /= m;
                for (int j = 0; j < m; j++)
                    c += abs(t - v[n / 2 * m + j]);
            }
        }

        if (m & 1 && m != 1) {
            int t = 0;
            for (int i = 0; i < n; i++)
                t += v[i * m + m / 2];

            if (n & 1) {
                t -= v[n / 2 * m + m / 2];
                t /= (m - 1);
                for (int i = 0; i < n; i++)
                    c += abs(t - v[i * m + m / 2]);
                c -= abs(t - v[n / 2 * m + m / 2]);
            } else {
                t /= n;
                for (int i = 0; i < n; i++)
                    c += abs(t - v[i * m + m / 2]);
            }
        }
        cout << c << eol;
    }
}