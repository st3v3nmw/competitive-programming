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
    
    int t, n;
    cin >> t;

    unsigned ll a, b, minA, minB, p, l;
    for (int i = 0; i < t; i++) {
        cin >> n;
        vector<unsigned ll> aa, bb;
        for (int j = 0; j < n; j++) {
            cin >> a;
            if (j == 0)
                minA = a;
            else if (a < minA)
                minA = a;
            aa.push_back(a);
        }

        for (int j = 0; j < n; j++) {
            cin >> b;
            bb.push_back(b);
            if (j == 0)
                minB = b;
            else if (b < minB)
                minB = b;
        }

        // debug(_(aa) << _(minA));
        // debug(_(bb) << _(minB));

        ll moves = 0;
        for (int j = 0; j < n; j++) {
            if (aa[j] > minA && bb[j] > minB) {
                p = min(aa[j] - minA, bb[j] - minB);
                l = max(aa[j] - minA, bb[j] - minB);
                moves += p + l - p;
                continue;
            }
            
            moves += (aa[j] - minA);
            moves += (bb[j] - minB);
        }
        cout << moves << eol;
    }
}