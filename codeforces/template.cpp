#include <bits/stdc++.h>

using namespace std;

#define debug(x) \
{ \
    ostringstream stream; \
    stream << x; \
    cerr << stream.str() << endl; \
}
#define _(x) #x << ": " << x << ", "
#define pb push_back
#define FOR(i, n) for (int i = 0; i < n; i++)
#define GCD(a,b) __gcd(a, b);
#define LCM(a,b) (a) * ((b) / __gcd(a, b));

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const ll MOD = 1e9 + 7;

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

// debugging i.e debug(_(c) << _(b));

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    return 0;
}