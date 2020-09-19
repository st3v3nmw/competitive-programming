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
    
    uint n, x, q;
    cin >> n >> x;
    vector<pair<uint, uint>> v(n); 
    for (uint d = 0; d < n; d++) {
        cin >> q;
        v[d] = {q, d};
    }
    sort(v.begin(), v.end());
    vector<tuple<uint, uint, uint>> v2;
    for (uint i = 0; i < n; i++) {
        for (uint j = i + 1; j < n; j++)
            v2.push_back({v[i].first + v[j].first, v[i].second, v[j].second});
    }

    for (uint i = 0; i < v2.size(); i++) {
        uint d = lower_bound(v.begin(), v.end(), pair<uint, uint>(x - get<0>(v2[i]), 0)) - v.begin();
        if (get<0>(v2[i]) + v[d].first == x && get<1>(v2[i]) != v[d].second && get<2>(v2[i]) != v[d].second) {
            vector<uint> pp = {get<1>(v2[i]), get<2>(v2[i]), v[d].second};
            sort(pp.begin(), pp.end());
            cout << pp[0] + 1 << " " << pp[1] + 1 << " " << pp[2] + 1 << eol;
            return 0;
        }
    }
    cout << "IMPOSSIBLE\n";
}