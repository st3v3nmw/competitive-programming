#include <bits/stdc++.h>

using namespace std;
#define ll long long

int main() {
    ll n;
    cin >> n;
    vector<ll> v1, v2;
    ll sum = n * (n + 1) / 2;
    if (sum % 2 != 0) {
        cout << "NO" << endl;
        return 0;
    }

    sum /= 2;
    for (int i = n; i > 0; i--) {
        if (sum - i >= 0) {
            v1.push_back(i);
            sum -= i;
        } else
            v2.push_back(i);
    }

    cout << "YES\n" << endl;
    cout << v1.size() << endl;
    for(int e : v1)
        cout << e << " ";
    cout << endl;
    cout << v2.size() << endl;
    for(int e : v2)
        cout << e << " ";
    cout << endl;
}