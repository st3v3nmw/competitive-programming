#include <bits/stdc++.h>
using namespace std;

vector<int> kmp(string const& s) {
    int s_len = s.size();
    vector<int> pi(s_len, 0);
    for (int i = 1; i < s_len; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    string s, p;
    cin >> s >> p;
    vector<int> pi = kmp(p + "$" + s);
    int c = 0;
    const int p_len = p.size();
    for (int e : pi)
        c += (e == p_len);
    cout << c << endl;
}