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

int path_count(vector<string> v, int n, char check, int r, int c) {
    v[0][0] = check;
    v[n - 1][n - 1] = check;
    v[r][c] = (v[r][c] == '0' ? '1' : '0');
    vector<vector<int>> t(n, vector<int>(n, 0));
    t[0][0] = 1;
    for (int i = 1; i < n; i++) {
        if (v[i][0] == check)
            t[i][0] = t[i - 1][0];
    }
    for (int j = 1; j < n; j++) {
        if (v[0][j] == check)
            t[0][j] = t[0][j - 1];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (v[i][j] == check)
                t[i][j] = t[i - 1][j] + t[i][j - 1];
        }
    }
    return t[n - 1][n - 1];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int g;
    cin >> g;
    for (int t = 0; t < g; t++) {
        int n;
        cin >> n;
        vector<string> v(n), v2;
        for (int i = 0; i < n; i++)
            cin >> v[i];
        vector<pair<int, int>> ans;
        int paths = path_count(v, n, '0', 0, 0) + path_count(v, n, '1', 0, 0);
        if (paths == 0) {
            cout << 0 << eol;
            continue;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((i == 0 && j == 0) || (i == n - 1 && j == n - 1))
                    continue;
                int c0 = path_count(v, n, '0', i, j);
                int c1 = path_count(v, n, '1', i, j);
                if (c0 + c1 == 0) {
                    ans.push_back({i + 1, j + 1});
                    goto end;
                } else if (paths > c0 + c1) {
                    ans.push_back({i + 1, j + 1});
                    paths = c0 + c1;
                }
            }
        }
        end:
        cout << ans.size() << eol;
        for (auto e : ans) {
            cout << e.first << " " << e.second << eol;
            v[e.first][e.second] = (v[e.first][e.second] == '0' ? '1' : '0');
        }
        // for (auto e : v)
        //     cout << e << eol;
        // cout << eol;
    }
}