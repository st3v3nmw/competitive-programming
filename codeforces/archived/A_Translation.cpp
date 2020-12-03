#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define debug(x) { ostringstream stream; stream << x; cout << stream.str() << eol; }
#define _(x) #x << ": " << x << ", "
#define ll long long
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    string w1, w2;
    cin >> w1;
    cin >> w2;

    if (w1.length() != w2.length()) {
        cout << "NO" << eol;
        return 0;
    }

    for (int i = 0; i < w1.length(); i++) {
        if (w1[i] != w2[w1.length() - i - 1]) {
            cout << "NO" << eol;
            return 0;
        }
    }
    cout << "YES" << eol;
}