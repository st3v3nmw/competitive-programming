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

vector<ll> sieve(ll n) {
    vector<bool> is_prime(n+1, true);
    vector<ll> primes;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    return primes;
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    // WA
    const ll Q = 17400;
    vector<ll> s = sieve(Q), seq;
    const int n = s.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
            seq.push_back(s[i] * s[j]);
    }

    sort(seq.begin(), seq.end());

    int t, k;
    cin >> t;
    for (int d = 0; d < t; d++) {
        cin >> k;
        cout << seq[k-1] << eol;
    }
}