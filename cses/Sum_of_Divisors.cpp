#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define ull unsigned ll
const ull MOD = 1e9 + 7;

ull modpow(int base, ull exp, ull modulus) {
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

void factors(ull n, map<ull, ull>& d) {
    ull i = 2;
    ull upper = floor(sqrt(n)) + 1;
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

ull divisors_sum(ull n) {
    if (n == 1)
        return 1;

    map<ull, ull> d;
    factors(n, d);
    uint result = 1;
    for (pair<ull, ull> e : d)
        result = (result * (modpow(e.first, e.second + 1, MOD) - 1) / (e.first - 1)) % MOD;
    return result;
}

int main() {
    ull n, sum = 1;
    cin >> n;
    for (ull i = 2; i <= n; i++)
        sum = (sum + divisors_sum(i)) % MOD;
    cout << sum << endl;
}