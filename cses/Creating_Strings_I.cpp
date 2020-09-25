#include <bits/stdc++.h>
using namespace std;

#define eol "\n"

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    vector<string> v = {s};
    while (next_permutation(s.begin(), s.end()))
        v.push_back(s);
    cout << v.size() << eol;
    for (string e : v)
        cout << e << eol;
}