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
    cin >> w;
    
    int l_count = 0, u_count = 0;
    
    for (int i = 0; i < w.length(); i++) {
    	if (islower(w[i]))
    		l_count += 1;
    	else
    		u_count += 1;
    }
    
    // debug(_(l_count) << _(u_count));
    
    if (l_count < u_count) {
        for (char c : w) {
            c = toupper(c);
            cout << c;
        }
    } else {
        for (char c : w) {
            c = tolower(c);
            cout << c;
        }
    }
    cout << endl;
}