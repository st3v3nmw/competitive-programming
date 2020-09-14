// debugging i.e debug(_(c) << _(b));

#define GCD(a,b) __gcd(a, b);
#define LCM(a,b) (a) * ((b) / __gcd(a, b));

long long binpow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1)
            result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

long long modpow(long long base, long long exp, long long modulus) {
    base %= modulus;
    long long result = 1;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}