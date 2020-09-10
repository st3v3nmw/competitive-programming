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
template <typename T> string to_str(set<T> x) { string r = "{"; for (auto t : x) r += to_str(t) + ", "; return r.substr(0, r.length() - 2) + "}"; }
template <typename T1, typename T2> string to_str(map<T1, T2> x) { string r = "{"; for (auto t : x) r += to_str(t.first) + ": " + to_str(t.second) + ", "; return r.substr(0, r.length() - 2) + "}"; }
#define ll long long
const ll MOD = 1e9 + 7;

// TODO: Optimize this

vector<ll> s_array;
const vector<ll>& suffix_array(const string& s) {
    s_array.clear();
    for (ll i = 0; i < s.size(); i++)
        s_array.push_back(i);

    size_t t = s.size();
    auto cmp = [&s, &t](ll a, ll b) {
        ll l = a > b ? t - a + 1 : t - b + 1;
        for (ll i = 0; i < l; i++) {
            if (s[a + i] > s[b + i])
                return true;
            else if (s[a + i] < s[b + i])
                return false;
        }
        return true;
    };

    sort(s_array.begin(), s_array.end(), cmp);
    return s_array;
}

ll n_repeated_substrs(const string& s) {
    vector<ll> arr = suffix_array(s), lcp;
    lcp.push_back(0);

    size_t t = s.size();
    auto commonPrefixLength = [&s, &t](ll a, ll b) {
        ll l = a > b ? t - a + 1 : t - b + 1;
        for (ll i = 0; i < l; i++) {
            if (s[a + i] != s[b + i])
                return i;
        }
        return l;
    };

    for (ll i = 1; i < s.size(); i++)
        lcp.push_back(commonPrefixLength(arr[i-1], arr[i]));

    unordered_set<string> substrs;
    string p, w;
    for (ll i = 1; i < lcp.size(); i++) {
        w = s.substr(arr[i]);
        for (ll j = 1; j <= lcp[i]; j++)
            substrs.insert(w.substr(0, j));
    }
    return substrs.size();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
    string s;
    while (t--) {
        cin >> s;
        cout << n_repeated_substrs(s) << eol;
    }
}