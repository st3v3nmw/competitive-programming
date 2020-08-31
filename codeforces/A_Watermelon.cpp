#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define debug(x) { ostringstream stream; stream << x; cout << stream.str() << eol; }
#define _(x) #x << ": " << x << ", "
#define ll long long
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int w;
    cin >> w;

    for (int i = 1; i < w; i++) {
    	for (int j = i; j < w; j++) {
    		if (i + j == w && i % 2 == 0 && j % 2 == 0) {
    			cout << "YES" << endl;
    			goto end;
    		}
    	}
    }
    cout << "NO" << endl;
    end:
    return 0;
}