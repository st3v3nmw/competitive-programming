#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define ll long long
#define ull unsigned ll
const ull MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int g;
    cin >> g;
    vector<int> v(g);
    ll sum = 0;
    for (int t = 0; t < g; t++) {
        cin >> v[t];
        sum += v[t];
    }
    ll pref = 0;
    int c = 0;
    for (int i = 0; i < g - 1; i++) {
        pref += v[i];
        sum -= v[i];
        if (pref == sum)
            c++;
    }
    cout << c << eol;
}