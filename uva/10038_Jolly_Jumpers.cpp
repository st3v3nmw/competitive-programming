#include <bits/stdc++.h>
using namespace std;
#define eol '\n'

int main() {
    string s;
    while(getline(cin, s)) {
        stringstream a = stringstream(s);
        int n, qi;
        vector<int> v;
        a >> n;
        while (n--) {
            a >> qi;
            v.push_back(qi);
        }
        n = v.size();
        vector<bool> bb(n - 1);
        for (int i = 0; i < n - 1; i++) {
            int q = abs(v[i] - v[i + 1]);
            if (q < n || q > 0)
                bb[q - 1] = true;
        }
        for (bool e : bb) {
            if (!e) {
                cout << "Not jolly\n";
                goto end;
            }
        }
        cout << "Jolly\n";
        end:
            continue;
    }
}