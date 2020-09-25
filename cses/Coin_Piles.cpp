#include <bits/stdc++.h>
using namespace std;

#define eol "\n"

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int t;
    cin >> t;
    int a, b;
    for (int d = 0; d < t; d++) {
        cin >> a >> b;
        if ((a + b) % 3 == 0 && min(a, b) * 2 >= max(a, b))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}