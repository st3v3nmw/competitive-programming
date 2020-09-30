#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define ll long long
#define ull unsigned ll

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ull g, c = 0, d = 2;
    cin >> g;
    int upper = sqrt(g);
    while (g > 1 && d <= upper) {
        if (g % d == 0) {
            cout << g / d << eol;
            return 0;
        } else
            d++;
    }
    cout << 1 << eol;
}