#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define ull unsigned long long

bool trial_division(int x) {
    ull upper = sqrt(x);
    for (int d = 2; d <= upper; d++) {
        if (x % d == 0)
            return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int g;
    cin >> g;
    for (int m = 1; m <= 1000; m++) {
        if (!trial_division(m * g + 1)) {
            cout << m << eol;
            break;
        }
    }
}