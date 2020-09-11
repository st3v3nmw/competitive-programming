#include <bits/stdc++.h>

using namespace std;
#define ll long long

int main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    if (n <= 3) {
        cout << "NO SOLUTION" << endl;
        return 0;
    }
    if (n % 2 == 0) {
        for (int i = n - 1; i > 0; i -= 2)
            cout << i << " ";
        for (int i = n; i > 0; i -= 2)
            cout << i << " ";
    } else {
        for (int i = n - 1; i > 0; i -= 2)
            cout << i << " ";
        for (int i = n; i > 0; i -= 2)
            cout << i << " ";
    }
}