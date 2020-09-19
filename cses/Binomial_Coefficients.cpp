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
#define ull unsigned long long
#define ll long long
const ull MOD = 1e9 + 7;

void f(ull n, vector<ull>& factorials) {
    ull result = 1;
    for (ull i = 2; i <= n; i++) {
        factorials.push_back(result);
        result = (__uint128_t) result * i % MOD;
    }
    factorials.push_back(result);
}

ull modpow(ull base, ull exp, ull modulus) {
    base %= modulus;
    ull result = 1;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ull t, a, b;
    vector<ull> factorials = {1};
    f(1000000, factorials);
    
    cin >> t;
    for (uint d = 0; d < t; d++) {
        cin >> a >> b;
        cout << (factorials[a] * modpow((factorials[b] * factorials[a - b]) % MOD, MOD - 2, MOD)) % MOD << endl;
    }
}