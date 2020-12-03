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

ll string_hash(string const& s) {
    const int p = 53; // Make p a prime number roughly equal to the number of characters in the input alphabet
    const ll m = 1e9 + 9;
    ll result = 0, p_pow = 1;
    for (char c : s) {
        result = (result + (c - 'A' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int k;
    string s, b;
    cin >> s >> b;
    cin >> k;
    bitset<26> bs(b);
    int s_len = s.size();
    unordered_set<ll> substrings;
    const int p = 31;
    const ll m = 32361122672259149; // now that's a prime (19th Lucas Prime)
    for (int i = 0; i < 26; i++)
        bs[i] = b[i] == '1';
    for (int i = 0; i < s_len; i++) {
        int curr_k = 0;
        ll hash_val = 0, p_pow = 1;
        for (int j = 1; j <= s_len - i; j++) {
            int c = s[i + j - 1] - 'a';
            if (!bs[c])
                curr_k++;
            if (curr_k > k)
                break;
            
            hash_val = (hash_val + (c + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
            substrings.insert(hash_val);
        }
    }
    cout << substrings.size() << endl;
}