#include <bits/stdc++.h>

using namespace std;
#define ll long long

int main() {
    ll sum = 0, n, e;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> e;
        sum += e;
    }
    cout << n * (n + 1) / 2 - sum << endl;
}