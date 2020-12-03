#include <bits/stdc++.h>
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

bool solve(int n, int curr, int sum, vector<int>& v) {
    if (n - sum == 0)
        return true;
    else if (n - sum < curr)
        return false;
    
    curr++;
    if (solve(n, curr, sum + curr, v))
        v.push_back(curr);
    else {
        curr++;
        if (solve(n, curr, sum + curr, v))
            v.push_back(curr);
        else
            return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int n, t = 0;
    cin >> n;
    vector<int> v;
    solve(n, 0, 0, v);
    cout << v.size() << eol;
    for (int i = v.size() - 1; i >= 0; i--)
        cout << v[i] << " ";
    cout << eol;
}