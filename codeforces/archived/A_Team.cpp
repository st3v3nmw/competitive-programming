#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define _(x) #x << ": " << to_str(x) << ", "
#define debug(x) { ostringstream stream; stream << x; cout << stream.str() << eol; }
string to_string(basic_string<char>& x) { return "\"" + x + "\""; }
string to_string(char x) { string r = ""; r += x; return "\'" + r + "\'";}
string to_string(bool x) { return x ? "true" : "false"; }
template <typename T> string to_str(T x) { return to_string(x); }
template <typename T1, typename T2> string to_str(pair<T1, T2> x) { return "(" + to_str(x.first) + ", " + to_str(x.second) + ")"; }
template <typename T> string to_str(vector<T> x) { string r = "{"; for (auto t : x) r += to_str(t) + ", "; return r + "}"; }
template <typename T1, typename T2> string to_str(map<T1, T2> x) { string r = "{"; for (auto t : x) r += to_str(t.first) + ": " + to_str(t.second) + ", "; return r + "}"; }
#define ll long long
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int t, f1, f2, f3, solved = 0;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> f1 >> f2 >> f3;
        if (f1 + f2 + f3 > 1)
            solved++;
    }
    cout << solved << eol;
}