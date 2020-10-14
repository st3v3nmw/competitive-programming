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

int main() {
    // ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int g;
    cin >> g;
    for (int t = 0; t < g; t++) {
        int n;
        cin >> n;
        ull upper = sqrt(n);
        vector<int> l, ans;
        map<int, bool> u, l_check;
        for (int d = 2; d <= upper; d++) {
            if (n % d == 0) {
                l.push_back(d);
                l_check[d] = false;
                if (n / d != upper)
                    u[n / d] = false;
            }
        }
        // debug(_(l));
        if (l.size() == 1)
            ans.push_back(l[0]);
        for (int i = 0; i < l.size() - 1; i++) {
            int n2 = l[i] * l[i + 1];
            if (!l_check[l[i]])
                ans.push_back(l[i]);
            if (u.find(n2) != u.end()) {
                ans.push_back(n2);
                u[n2] = true;
            } else if (l_check.find(n2) != l_check.end()) {
                ans.push_back(n2);
                l_check[n2] = true;
            }
        }
        if (l.size() > 1)
            ans.push_back(l[l.size() - 1]);
        for (pair<int, bool> p : u) {
            if (!p.second)
                ans.push_back(p.first);
        }
        // ans.push_back(n);

        // for (int i = 0; i < ans.size() - 2; i++) {
        //     if (__gcd(ans[i], ans[i + 1]) == 1)
        //         swap(ans[i + 1], ans[i + 2]);
        // }
        sort(ans.begin(), ans.end());
        unordered_set<int> ans2;
        vector<int> ans3;
        for (int i = 0; i < ans.size(); i++) {
            if (ans2.find(ans[i]) == ans2.end()) {
                ans2.insert(ans[i]);
                ans3.push_back(ans[i]);
            }

            for (int j = i + 1; j < ans.size(); j++) {
                if (ans[j] > n / ans[i])
                    break;
                if (ans[j] % ans[i] == 0) {
                    if (ans2.find(ans[j]) == ans2.end()) {
                        ans2.insert(ans[j]);
                        ans3.push_back(ans[j]);
                    }
                }
            }
        }
        ans3.push_back(n);
        debug(_(ans3));
        // exit(0);
        int c = __gcd(ans[0], ans[ans.size() - 1]) == 1;
        for (int i = 0; i < ans.size() - 1; i++) {
            if (__gcd(ans[i], ans[i + 1]) == 1)
                c++;
        }
        // debug(_(ans));
        // for (int e : ans)
        //     cout << e << " ";
        cout << eol << c << eol;
    }
}