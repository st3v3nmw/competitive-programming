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

inline float dist(int x1, int y1, int x2, int y2) {
    return sqrt(abs(x1 - x2) + abs(y1 - y2));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int t, cx, cy, ex, ey;
    cin >> t >> cx >> cy >> ex >> ey;
    char c;
    int d;
    for (d = 0; d < t; d++) {
        if (cx == ex && ey == cy) {
            cout << d << eol;
            return 0;
        }

        cin >> c;
        if (c == 'N') {
            if (dist(cx, cy + 1, ex, ey) <= dist(cx, cy, ex, ey))
                cy += 1;
        } else if (c == 'S') {
            if (dist(cx, cy - 1, ex, ey) <= dist(cx, cy, ex, ey))
                cy -= 1;
        } else if (c == 'E') {
            if (dist(cx + 1, cy, ex, ey) <= dist(cx, cy, ex, ey))
                cx += 1;
        } else {
            if (dist(cx - 1, cy, ex, ey) <= dist(cx, cy, ex, ey))
                cx -= 1;
        }
    }

    if (cx == ex && ey == cy)
        cout << d << eol;
    else
        cout << -1 << eol;
}