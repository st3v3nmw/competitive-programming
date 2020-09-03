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

    // TODO: fix this
    
    int t, n, w;
    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n;
        vector<int> bb;
        int a = 0;
        for (int j = 0; j < n; j++) {
            cin >> w;
            bb.push_back(w);
        }

        bool setN = false;
        int maxN = 0;
        for (int s = 2; s < 2 * n + 1; s++) {
            int n_teams = 0;
            // debug(_(s));
            bitset<50> teams;
            for (int j = 0; j < n - 1; j++) {
                if (teams[j])
                    continue;

                for (int k = j + 1; k < n; k++) {
                    if (teams[k])
                        continue;
                    
                    if (bb[j] + bb[k] == s) {
                        n_teams++;

                        teams[j] = 1;
                        teams[k] = 1;
                        break;
                    }
                }
            }

            if (!setN) {
                maxN = n_teams;
                setN = true;
            } else if (n_teams > maxN) {
                maxN = n_teams;
            }
        }

        cout << maxN << eol;
    }
}