#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define ll long long

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll t;
    cin >> t;
    vector<ll> v(t);
    for (ll d = 0; d < t; d++)
        cin >> v[d];
    ll moves = 0;
    for (ll i = 1; i < t; i++) {
        if (v[i] < v[i - 1]) {
            moves += v[i - 1] - v[i];
            v[i] = v[i - 1];
        }
    }
    cout << moves << eol;
}