#include <bits/stdc++.h>

using namespace std;
#define ll long long

int divisors(int n) {
    if (n == 1)
        return 1;
    map<int, int> d;
    int i = 2;
    int upper = floor(sqrt(n)) + 1;
    while(i <= upper) {
        if (n % i == 0) {
            if (d.find(i) == d.end())
                d.insert({i, 1});
            else
                d[i]++;
            n /= i;
        } else 
            i++;
    }

    if (n != 1)
        d.insert({n, 1});

    int result = 1;
    for (pair<int, int> e : d)
        result *= (e.second + 1);
    if (result == 1)
        result = 2;
    return result;
}

int main() {
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        cout << divisors(n) << endl;
    }
}