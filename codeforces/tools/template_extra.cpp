// debugging i.e debug(_(c) << _(b));

// __gcd(a, b)

// exponentiation
uint binpow(int base, uint exp) {
    uint result = 1;
    while (exp > 0) {
        if (exp & 1)
            result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

uint modpow(int base, uint exp, uint modulus) {
    base %= modulus;
    uint result = 1;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

// random numbers
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
shuffle(v.begin(), v.end(), rng);
