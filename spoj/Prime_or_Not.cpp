#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define ull unsigned long long
#define ll long long
const ull MOD = 1e9 + 7;

uint64_t modpow(uint64_t base, uint64_t exp, uint64_t modulus) {
    base %= modulus;
    ull result = 1;
    while (exp > 0) {
        if (exp & 1)
            result = (__uint128_t) result * base % modulus;
        base = (__uint128_t) base * base % modulus;
        exp >>= 1;
    }
    return result;
}

bool check_composite(uint64_t n, uint64_t a, uint64_t d, uint s) {
    uint64_t x = modpow(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (uint r = 1; r < s; r++) {
        x = (__uint128_t) x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

bool rabin_miller(uint64_t n) {
    if (n < 2)
        return false;
    uint r = 0;
    uint64_t d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (uint a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) { // can test up to 64 bit numbers
        if (n == a)
            return true;
        if(check_composite(n, a, d, r))
            return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    uint t;
    cin >> t;
    ull n;
    for (uint d = 0; d < t; d++) {
        cin >> n;
        cout << (rabin_miller(n) ? "YES" : "NO") << eol;
    }
}