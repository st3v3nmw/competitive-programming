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

int main() {
    int g, t, st, m;
    cin >> g;
    while (g--) {
        cin >> t;
        map<char, long long> mp;
        char c;
        while (t--) {
            cin >> c >> st;
            mp[c] = st;
        }
        double cost = 0;
        cin >> m;
        m++;
        while (m--) {
            string s;
            getline(cin, s);
            for (char c : s) {
                if (mp.find(c) != mp.end())
                    cost += mp[c];
            }
        }
        cost /= 100;
        printf("%llu.%d$\n", (long long) floor(cost), (int) (floor((cost - floor(cost)) * 100)));
    }
}