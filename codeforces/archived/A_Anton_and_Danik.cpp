#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define _(x) #x << ": " << x << ", "
#define debug(x) { ostringstream stream; stream << x; cout << stream.str() << eol; }
#define ll long long
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    unsigned int T, A_count = 0, D_count = 0;
    cin >> T;
    char c;
    for (int i = 0; i < T; i++) {
        cin >> c;
        if (c == 'A')
            A_count++;
        else
            D_count++;
    }

    if (A_count > D_count) {
        cout << "Anton" << eol;
    } else if (A_count < D_count) {
        cout << "Danik" << eol;
    } else {
        cout << "Friendship" << eol;
    }
}