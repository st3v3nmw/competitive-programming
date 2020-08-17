#include <bits/stdc++.h>

using namespace std;

#define debug(x) \
{ \
    ostringstream stream; \
    stream << x; \
    cerr << stream.str() << endl; \
}
#define _(x) #x << ": " << x << ", "
#define pb push_back
#define FOR(i, n) for (i = 0; i < n; i++)
#define GCD(a,b) __gcd(a, b);
#define LCM(a,b) (a) * ((b) / __gcd(a, b));
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const ll MOD = 1e9 + 7;

// debugging i.e debug(_(c) << _(b));

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, col, row;
    cin >> n;
    string coord;
    for (int i = 0; i < n; i++) {
        cin >> coord;
        if (coord[0] == 'R' && isdigit(coord[1]) && coord.find('C') != -1) {
            vector<char> result;
            for (int i = 0; i < coord.length(); i++) {
                if (coord[i] == 'R')
                    row = atoi(&coord[i + 1]);
                else if (coord[i] == 'C') {
                    col = atoi(&coord[i + 1]);
                    break;
                }
            }
            bool d = false;
            do {
                if (col % 26 == 0) {
                    if (d)
                        result.push_back('Y');
                    else
                        result.push_back('Z');
                    d = true;
                } else if (d) {
                    d = false;
                    if (col % 26 != 1)
                        result.push_back(char(col % 26 + 63));
                } else
                    result.push_back(char(col % 26 + 64));
                col /= 26;
            } while (col != 0);

            int s = result.size() - 1;
            for (int i = 0; i <= s; i++)
                cout << result[s - i];
            cout << row << endl;
            
        } else {
        	debug(_(coord));
            col = int(coord[0]) - 64;
            for (int i = 1; i < coord.length(); i++) {
                if (isalpha(coord[i])) {
                    col =  col * 26 + int(coord[i]) - 64;
                } else {
                    row = atoi(&coord[i]);
                    break;
                }
            }
            cout << "R" << row << "C" << col << endl;
            debug(_(row) << _(col));
        }
    }
    return 0;
}