#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define eol "\n"
#define _(x) #x << "=" << to_str(x) << ", "
#define debug(x) { ostringstream stream; stream << x; string s = stream.str(); cout << s.substr(0, s.length() - 2) << eol; }
string to_string(basic_string<char>& x) { return "\"" + x + "\""; }
string to_string(char x) { string r = ""; r += x; return "\'" + r + "\'";}
string to_string(bool x) { return x ? "true" : "false"; }
template <typename T> string to_str(T x) { return to_string(x); }
template <typename T1, typename T2> string to_str(pair<T1, T2> x) { return "(" + to_str(x.first) + ", " + to_str(x.second) + ")"; }
template <typename T> string to_str(vector<T> x) { string r = "{"; for (auto t : x) r += to_str(t) + ", "; return r.substr(0, r.length() - 2) + "}"; }
template <typename T1, typename T2> string to_str(map<T1, T2> x) { string r = "{"; for (auto t : x) r += to_str(t.first) + ": " + to_str(t.second) + ", "; return r.substr(0, r.length() - 2) + "}"; }
#define ll long long
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    // TODO: Fix this
    int n, d;
    cin >> n >> d;
    string lilies;
    cin >> lilies;
    int pos = 1, jumps = 0;
    while (pos < n) {
    	bool jumped = false;
    	for (int i = d; i > 0; i--) {
    		if (lilies[pos + i - 1] == '1') {
    			pos += i;
    			jumps++;
    			jumped = true;
    			break;
    		}
    	}
    	
    	if (!jumped) {
			// cout << pos << eol;
    		cout << -1 << eol;
    		goto end;
    	}
    }
    cout << jumps << eol;
    end:
    return 0;
}