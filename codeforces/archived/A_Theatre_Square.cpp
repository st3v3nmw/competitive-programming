#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define debug(x) { ostringstream stream; stream << x; cout << stream.str() << eol; }
#define _(x) #x << ": " << x << ", "
#define ll long long
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    unsigned ll m, n, a;
    cin >> m >> n >> a;
    cout << (m / a + (m % a ? 1 : 0)) * (n / a + (n % a ? 1 : 0)) << eol;
}