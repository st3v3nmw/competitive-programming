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
    
    int g, w, h;
    cin >> g;
    ll width = 0;
    vector<pair<int, int>> us, hs;
    map<int, int, greater<int>> mp;
    for (int t = 0; t < g; t++) {
        cin >> w >> h;
        width += w;
        us.push_back({w, h});
        mp[h]++;
    }

    for (const auto& p : mp)
        hs.push_back({p.second, p.first});
    ll total = hs[0].second * width;
    if (hs[0].first > 1) {
        for (pair<int, int> e : us)
            cout << total - e.first * hs[0].second << " ";
        cout << eol;
    } else {
        for (pair<int, int> e : us) {
            if (e.second == hs[0].second)
                cout << hs[1].second * width - e.first * hs[1].second << " ";
            else
                cout << total - e.first * hs[0].second << " ";
        }
        cout << eol;
    }
}