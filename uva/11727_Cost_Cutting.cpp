#include <bits/stdc++.h>
using namespace std;
#define eol "\n"

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        vector<int> v(3);
        cin >> v[0] >> v[1] >> v[2];
        sort(v.begin(), v.end());
        cout << "Case " << i + 1 << ": " << v[1] << eol;
    }
}