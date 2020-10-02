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
    
    ull g, n;
    cin >> g >> n;
    vector<char> a(g);
    unordered_set<char> b;
    char p;
    for (ull t = 0; t < g; t++)
        cin >> a[t];
    for (ull t = 0; t < n; t++) {
        cin >> p;
        b.insert(p);
    }
    for (ull t = 0; t < g; t++) {
        if (b.find(a[t]) != b.end())
            a[t] = '1';
        else
            a[t] = '0';
    }
    // debug(_(a));
    ull p1 = 0, p2 = 1;
    ull t = 0;
    while (p1 != p2 && p1 < g && p2 < g) {
        while (a[p2] == '1' && p2 < g)
            p2++;
        while (a[p1] == '0' && p1 < p2 - 1)
            p1++;
        // cout << p1 << " " << p2 << eol;
        if (a[p1] == '1' && (a[p2] == '0' || p2 == g))
            t += ((p2 - p1) * (p2 - p1 + 1)) / 2;
        p1 = p2; p2++;
    }
    cout << t << eol;
}