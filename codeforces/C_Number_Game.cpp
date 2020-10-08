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

bool trial_division(int x) {
    ull upper = sqrt(x);
    for (int d = 2; d <= upper; d++) {
        if (x % d == 0)
            return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int g, q;
    cin >> g;
    for (int t = 0; t < g; t++) {
        cin >> q;
        if (q == 1)
            cout << "FastestFinger\n";
        else if (q & 1 || q == 2)
            cout << "Ashishgup\n";
        else {
            int q1 = q;
            while (!(q1 & 1))
                q1 /= 2;
            
            if (q1 == 1)
                cout << "FastestFinger\n";
            else {
                if (q % 4 == 0) 
                    cout << "Ashishgup\n";
                else {
                    q /= 2;
                    if (trial_division(q))
                        cout << "FastestFinger\n";
                    else
                        cout << "Ashishgup\n";
                }
                    
            }
        }
    }
}