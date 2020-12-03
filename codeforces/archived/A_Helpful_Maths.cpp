#include <bits/stdc++.h>
using namespace std;

#define eol "\n"
#define debug(x) { ostringstream stream; stream << x; cout << stream.str() << eol; }
#define _(x) #x << ": " << x << ", "
#define ll long long
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    string s;
    cin >> s;
    vector<int> v;
    char * c;
    for (int i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) {
            c = &s[i];
            v.push_back(atoi(c));
        }
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i != v.size() - 1)
            cout << "+";
    }
}