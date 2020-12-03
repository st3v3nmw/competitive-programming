#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define _(x) #x << "=" << to_str(x) << ", "
#define debug(x) { ostringstream stream; stream << x; string s = stream.str(); cout << s.substr(0, s.length() - 2) << eol; }
string to_string(basic_string<char>& x) { return "\"" + x + "\""; }
string to_string(char x) { string r = ""; r += x; return "\'" + r + "\'";}
template <typename T> string to_str(T x) { return to_string(x); }
template <typename T1, typename T2> string to_str(pair<T1, T2> x) { return "(" + to_str(x.first) + ", " + to_str(x.second) + ")"; }
template <typename T> string to_str(vector<T> x) { string r = "{"; for (auto t : x) r += to_str(t) + ", "; return r.substr(0, r.length() - 2) + "}"; }
template <typename T1, typename T2> string to_str(map<T1, T2> x) { string r = "{"; for (auto t : x) r += to_str(t.first) + ": " + to_str(t.second) + ", "; return r.substr(0, r.length() - 2) + "}"; }
#define ll long long
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int t, n, k;
    char c;
    cin >> t;
    for (int d = 0; d < t; d++) {
        cin >> n >> k;
        int free = 0, count = 0, block = 0;
        for (int i = 0; i < n; i++) {
            cin >> c;
            if (c == '0') {
                free++;
            } else {
                if (block == 0 && free > 0) {
                    free -= k;
                    count += ceil(free / (k + 1.0));
                } else if (block != 0) {
                    free -= 2 * k;
                    if (free > 0)
                        count += ceil(free / (k + 1.0));
                }

                free = 0;
                block++;
            }
        }
        if (free != 0 && block != 0) {
            free -= k;
            count += ceil(free / (k + 1.0));
        }

        if (block == 0)
            count = ceil(free / (k + 1.0));
        cout << count << eol;
    }
}