#include <iostream>
#include <vector>
#include <map>
#include <sstream>
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

    // TODO: Optimize this
    
    int t = 1, n;
    cin >> t;
    vector<ll> v;
    vector<vector<int>> dp; // <len, previous, idx>
    vector<ll> cost;
    ll e;
    while (t--) {
        cin >> n;
        v.clear();
        dp.clear();
        cost.clear();
        for (int i = 0; i < n; i++) {
        	cin >> e;
        	v.push_back(e);
        	dp.push_back({1, i, i});
        	cost.push_back(-1e18);
        }
        
        cost[0] = v[0];
        ll bestCost;
        int bestCostJ, bestLen;
        for (int i = 1; i < n; i++) {
        	bestCost = -1e18; bestLen = 0;
        	for (int j = 0; j < i; j++) {
        		if (v[i] / abs(v[i]) != v[j] / abs(v[j]) && dp[j][0] + 1 >= dp[i][0]) {
        			if (dp[j][0] > bestLen) {
        				bestLen = dp[j][0];
        				bestCost = cost[j] + v[i];
        				bestCostJ = j;
        			} else if (dp[j][0] == bestLen && cost[j] + v[i] > bestCost) {
        				bestCost = cost[j] + v[i];
        				bestCostJ = j;
        			}
        		}
        	}
        	
        	if (bestCost > -1e17) {
        		dp[i][0] = dp[bestCostJ][0] + 1;
        		dp[i][1] = bestCostJ;
        		cost[i] = bestCost;
        	}
        	
        	if (cost[i] < -1e17)
        		cost[i] = v[i];
        }
        
        int mx = 1;
        for (vector<int> p : dp) {
        	if (p[0] > mx)
        		mx = p[0];
        }
        
        //cout << eol;
        
        if (mx == 1) {
        	cout << -1 << eol;
        	continue;
        }
        
        ll maxTot = -1e18, curr;
        for (vector<int> p : dp) {
        	if (p[0] == mx) {
        		int m = mx;
        		curr = 0;
        		while (m--) {
        			//cout << v[p[2]] << " ";
        			curr += v[p[2]];
        			p = dp[p[1]];
        		}
        	//	cout << curr << eol;
        	if (curr > maxTot)
        		maxTot = curr;
        	}
        }
        
        cout << maxTot << eol;
       // debug(_(v));
        //debug(_(cost));
      // debug(_(dp));
    }
}