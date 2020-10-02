#include <bits/stdc++.h>
using namespace std;

#define eol "\n"

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    bitset<10> v;
    int n;
    cin >> n;
    char c;
    for (int i = 0; i < n; i++) {
        cin >> c;
        if (c == 'L') {
            for (int j = 0; j < 10; j++) {
                if (!v[j]) {
                    v[j] = 1;
                    break;
                }
            }
        } else if (c == 'R') {
            for (int j = 9; j >= 0; j--) {
                if (!v[j]) {
                    v[j] = 1;
                    break;
                }
            }
        } else
            v[c - '0'] = 0;
    }
    string s = v.to_string();
    reverse(s.begin(), s.end());
    cout << s << eol;
}