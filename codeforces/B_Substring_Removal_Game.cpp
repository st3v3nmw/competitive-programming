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
        string s;
        cin >> s;
        vector<int> v;
        int cnt = s[0] == '1';
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == '1')
                cnt++;
            else if (cnt > 0) {
                v.push_back(cnt);
                cnt = 0;
            }
        }

        if (cnt > 0)
            v.push_back(cnt);

        sort(v.rbegin(), v.rend());
        ll score = 0;
        for (int i = 0; i < v.size(); i += 2)
            score += v[i];
        cout << score << eol;
    }
}