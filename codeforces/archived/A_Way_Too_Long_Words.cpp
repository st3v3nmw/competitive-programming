#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define debug(x) { ostringstream stream; stream << x; cout << stream.str() << eol; }
#define _(x) #x << ": " << x << ", "
#define ll long long
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    string w;
    int t, len;
    cin >> t;
    
    for (int i = 0; i < t; i++) {
    	cin >> w;
    	if (w.length() <= 10) {
    		cout << w << endl;
    	} else {
    		cout << w[0] << w.length() - 2 << w[w.length() - 1] << endl;
    	}
    }
}