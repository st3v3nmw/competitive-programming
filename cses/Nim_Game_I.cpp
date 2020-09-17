#include <bits/stdc++.h>
using namespace std;

#define eol "\n"

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    uint t, n, q, r;
    cin >> t;
    for (uint d = 0; d < t; d++) {
        cin >> n;
        for (uint i = 0; i < n; i++) {
            cin >> q;
            if (i == 0)
                r = q;
            else
                r ^= q;
        }
        if (r > 0)
            cout << "first" << eol;
        else
            cout << "second" << eol;
    }
}