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
    
    int t, n, e, li, ui;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++)
            cin >> v[i];
        
        bool l_set, u_set;
        for (int i = 1; i < n; i++) {
            l_set = u_set = false;
            for (int j = 0; j < i; j++) {
                if (v[j] < v[i]) {
                    li = j + 1;
                    l_set = true;
                    break;
                }
            }
            for (int j = i + 1; j < n; j++) {
                if (v[j] < v[i]) {
                    ui = j + 1;
                    u_set = true;
                    break;
                }
            }

            if (l_set && u_set) {
                cout << "YES\n";
                cout << li << " " << i + 1 << " " << ui << eol;
                goto end;
            }
        }
        cout << "NO\n";
        end:
        continue;
    }
}