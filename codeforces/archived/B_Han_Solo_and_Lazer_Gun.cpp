#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define INF INT_MAX

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    double g, x0, y0, a, b;
    cin >> g >> x0 >> y0;
    map<double, int> mp;
    for (int t = 0; t < g; t++) {
        cin >> a >> b;
        if (a - x0 == 0)
            mp[INT_MAX]++;
        else
            mp[(b -y0) / (a - x0)]++;
    }
    cout << mp.size() << eol;
}