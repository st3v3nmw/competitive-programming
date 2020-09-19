#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
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
#define ull unsigned ll
const ull MOD = 1e9 + 7;
 
void subsetSums(const vector<ull>& v, uint start, uint end, vector<ull>& sums) {
    ull d = end - start;
    for (uint i = 0; i < pow(2, d); i++) {
        ull i2 = i, sum = 0, j = 0;
        do {
            if (i2 & 1)
                sum += v[start + j];
            i2 /= 2;
            j++;
        } while (i2 != 0);
        sums.push_back(sum);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ull n, x;
    cin >> n >> x;
    vector<ull> v(n);
    for (uint d = 0; d < n; d++)
        cin >> v[d];
 
    sort(v.begin(), v.end());
    vector<ull> v1;
    subsetSums(v, 0, v.size() / 2, v1);
    vector<ull> v2;
    subsetSums(v, v.size() / 2, v.size(), v2);
    sort(v2.begin(), v2.end());
 
    // debug(_(v1) << _(v2));
 
    ull count = 0;
    for (ull e : v1) {
        ull d = lower_bound(v2.begin(), v2.end(), x - e) - v2.begin();
        for (ull i = d; i < v2.size(); i++) {
            if (e + v2[i] > x)
                break;
            if (e + v2[i] == x) {
                count++;
            }
        }
    }
    cout << count << endl;
}