#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define ll long long
#define ull unsigned ll

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ull g, x, y;
    cin >> g;
    for (int t = 0; t < g; t++) {
        cin >> x >> y;
        if (x - y == 1)
            cout << "NO\n";
        else
            cout << "YES\n";
    }
}