// debugging i.e debug(_(c) << _(b));

#define GCD(a,b) __gcd(a, b);
#define LCM(a,b) (a) * ((b) / __gcd(a, b));

template <typename T>
T modpow(T base, T exp, T modulus) {
    base %= modulus;
    T result = 1;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}