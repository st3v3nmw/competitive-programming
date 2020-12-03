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
        cin >> n;
        vector<int> v(n);
        vector<bool> used(n);
        int mmax = 0, idx = 0;
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            if (v[i] > mmax) {
                idx = i;
                mmax = v[i];
            }
        }
        if (n == 1) {
            cout << v[0] << eol;
            continue;
        }

        cout << mmax << " ";
        used[idx] = true;

        vector<int> gcd = {mmax};
        for (int i = 0; i < n - 1; i++) {
            int mmax = 0, idx1 = 0;
            for (int j = 0; j < n; j++) {
                if (__gcd(gcd[gcd.size() - 1], v[j]) > mmax && !used[j]) {
                    mmax = __gcd(gcd[gcd.size() - 1], v[j]);
                    idx1 = j;
                }
            }
            cout << v[idx1] << " ";
            gcd.push_back(mmax);
            used[idx1] = true;
        }
        cout << eol;
    }
}