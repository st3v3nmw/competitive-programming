#include <bits/stdc++.h>

using namespace std;
#define ll long long

template <typename T>
T modpow(T base, T exp) {
    base %= 1000000007;
    T result = 1;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % 1000000007;
        base = (base * base) % 1000000007;
        exp >>= 1;
    }
    return result;
}

int main() {
    long long n, b = 2;
    cin >> n;
    cout << modpow(b, n) << endl;
}