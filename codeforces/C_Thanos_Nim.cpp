#include <bits/stdc++.h>
using namespace std;

int main() {
    int g;
    cin >> g;
    vector<int> v(g);
    for (int i = 0; i < g; i++)
        cin >> v[i];
    sort(v.begin(), v.end());
    cout << (v[0] == v[g / 2] ? "Bob\n" : "Alice\n");
}