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
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int t, n;
    cin >> t >> n;
    vector<string> v(t), rev(t);
    bitset<100> used;
    for (int i = 0; i < t; i++) {
        cin >> v[i];
        string s = "";
        for (int j = n - 1; j >= 0; j--)
            s += v[i][j];
        rev[i] = s;
    }

    vector<string> start, end;
    string middle;
    for (int i = 0; i < t; i++) {
        if (used[i])
            continue;
        if (v[i] == rev[i]) {
            middle = v[i];
            continue;
        }

        for (int j = i + 1; j < t; j++) {
            if (v[i] == rev[j]) {
                start.push_back(v[i]);
                end.push_back(v[j]);
                used[j] = 1;
            }
        }
    }

    string r = "";
    for (string e : start)
        r += e;
    r += middle;
    for (int i = end.size() - 1; i >= 0; i--)
        r += end[i];
    cout << r.size() << eol << r << eol;
}