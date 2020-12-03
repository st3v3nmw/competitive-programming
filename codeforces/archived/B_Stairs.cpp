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

// bool nice(ll n) {
//     ll k = ceil(n / 2.0), sum = 0, i = 1;
//     while (k > 0) {
//         sum += k * i * i;
//         i *= 2;
//         k /= 2;
//     }
//     return (n * (n + 1)) / 2 == sum;
// }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    vector<ull> v = {1, 7, 35, 155, 651, 2667, 10795, 43435, 174251, 698027, 2794155, 11180715, 44731051, 178940587, 715795115, 2863245995, 11453115051, 45812722347, 183251413675, 733006703275, 2932028910251, 11728119835307, 46912487729835, 187649967696555, 750599904340651, 3002399684471467, 12009598872103595, 48038395756849835, 192153583564270251, 768614335330822827};

    int t;
    cin >> t;
    ull q;
    for (int d = 0; d < t; d++) {
        cin >> q;
        if (q == 1) {
            cout << 1 << eol;
            continue;
        }
        for (int n = 1; n <= 30; n++) {
            if (v[n - 1] > q) {
                cout << n - 1 << eol;
                goto end;
            }
        }
        cout << 30 << eol;
        end:
            continue;
    }
}