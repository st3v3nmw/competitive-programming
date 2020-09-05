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

bool contains(vector<int> bb, int x, int y) {
    bool hasX = false, hasY = false;
    for (int a : bb) {
        if (a == x) hasX = true;
        if (a == y) hasY = true;
    }
    return hasX && hasY;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    // max possible diff (y - x)
    int t;
    cin >> t;
    int n, x, y;
    while (t--) {
        cin >> n >> x >> y;

        vector<int> v;
        for (int d = 1; d < 50; d++) {
            for (int a = 1; a < 50; a++) {
                v.clear();
                int i = a;
                for (int j = 1; j <= n; j++) {
                    v.push_back(i);
                    i += d;
                }

                if (contains(v, x, y) && v.size() == n)
                    goto end;
            }
        }

        end:
        for (auto x : v)
            cout << x << " ";
        cout << eol;
    }
}