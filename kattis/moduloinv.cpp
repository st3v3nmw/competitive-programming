#include <iostream>

using namespace std;

template <typename T>
T totient(T n) {
    /*
        Euler's totient function φ
        φ(n) is defined as the number of positive integers <= n that are relatively prime to n
        i.e. if n is a prime, then φ(n) = n - 1
    */
    T r = n, m = n;
    for (long long i = 2; i < n + 1; i++) {
        if (m % i == 0) {
            r *= (1 - 1 / (double) i);
            while (m % i == 0)
                m /= i;
        }
        if (m == 1)
            break;
    }
    return r;
}

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

template <typename T>
T modinv(T a, T m) {
    return modpow(a, totient(m) - 1, m) % m;
}

int main() {
    cout << totient(5) << endl;
    cout << totient(6) << endl;
    cout << totient(10) << endl;
}