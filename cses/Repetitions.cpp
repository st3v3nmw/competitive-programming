#include <bits/stdc++.h>

using namespace std;
#define ll long long

int main() {
    string s;
    cin >> s;
    char curr = 'Q';
    int currLen = 0, mx = 0;
    for (char c : s) {
        if (c != curr) {
            mx = max(currLen, mx);
            curr = c;
            currLen = 1;
        } else
            currLen++;
    }
    cout << max(currLen, mx) << endl;
}