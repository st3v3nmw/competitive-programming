#include <bits/stdc++.h>
using namespace std;

#define eol "\n"

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    uint t, n = 0;
    cin >> t;
    for (uint d = 5; d <= t; d *= 5)
        n += t / d;
    cout << n << eol;
}