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
const ull MOD = pow(2, 30);

void factors(int n, map<int, int>& d) {
    int i = 2;
    int upper = floor(sqrt(n)) + 1;
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
}

int divisors_count(int n) {
    if (n == 1)
        return 1;

    map<int, int> d;
    factors(n, d);
    int result = 1;
    for (pair<int, int> e : d)
        result *= (e.second + 1);
    return result;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int a, b, c;
    cin >> a >> b >> c;
    ull sum = 0;
    map<int, int> m;
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            for (int k = 1; k <= c; k++) {
                if (m.find(i * j * k) == m.end())
                    m[i * j * k] = divisors_count(i * j * k);
                sum += m[i * j * k];
                sum %= MOD;
            }
        }
    }
    cout << sum << eol;
}