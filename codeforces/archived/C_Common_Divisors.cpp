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

template <typename T>
T gcd_arr(const vector<T>& arr) {
    T gcd_r = arr[0];
    for (auto num : arr)
        gcd_r = __gcd(gcd_r, num);
    return gcd_r;
}

ll divisors(ll n) {
    if (n == 1)
        return 1;
    map<ll, ll> d;
    ll i = 2;
    ll upper = floor(sqrt(n)) + 1;
    while(i <= upper) {
        if (n % i == 0) {
            if (d.find(i) == d.end())
                d.insert({i, 1});
            else
                d[i]++;
            n /= i;
        } else 
            i++;
    }

    if (n != 1)
        d.insert({n, 1});

    ll result = 1;
    for (pair<ll, ll> e : d)
        result *= (e.second + 1);
    if (result == 1)
        result = 2;
    return result;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    // this problem has made so happy LOL
    
    ll t;
    cin >> t;
    ll a;
    vector<ll> v;
    while (t--) {
        cin >> a;
        v.push_back(a);
    }

    cout << divisors(gcd_arr(v)) << eol;
}