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
    
    unsigned int t;
    cin >> t;
    vector<ull> q;
    ull count = 0, p;
    for (int d = 0; d < t; d++) {
        cin >> p;
        q.push_back(p);
    }

    if (t == 1) {
        cout << 0 << endl;
        cout << q[0] << endl;
        return 0;
    }

    sort(q.begin(), q.end());

    ull sz = q.size() / 2;
    vector<int> v;
    for (int d = 0; d < sz; d++) {
        v.push_back(q[sz + d]);
        v.push_back(q[d]);
    }
    if (t % 2 == 1)
        v.push_back(q[t - 1]);
    ull c = 0;
    for (int i = 1; i < v.size() - 1; i++)
        c += (v[i] < v[i - 1] && v[i] < v[i + 1]);
    cout << c << eol;
    for (int e : v)
        cout << e << " ";
    cout << eol;
}