#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned ll
const ull MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    uint t;
    cin >> t;
    ull q;
    vector<bool> seen(1000000000);
    uint count = 0;
    for (uint d = 0; d < t; d++) {
        cin >> q;
        if (!seen[q]) {
            count++;
            seen[q] = true;
        }
    }
    cout << count << endl;
}