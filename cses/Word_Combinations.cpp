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

vector<pair<int, int>> kmp(string const& s, int sb_len) {
    int s_len = s.size();
    vector<int> pi(s_len, 0);
    for (int i = 1; i < s_len; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    vector<pair<int, int>> b;
    for (int i = sb_len + 1; i < s_len; i++) {
        if (pi[i] == sb_len) {
            int start = i - 2 * sb_len;
            b.push_back({start, start + sb_len});
        }
    }
    return b;
}

// TODO

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    string s, sb;
    cin >> s;
    int t;
    cin >> t;
    for (int d = 0; d < t; d++) {
        cin >> sb;
        vector<pair<int, int>> qq = kmp(sb + "$" + s, sb.size());
        debug(_(qq));
    }
}