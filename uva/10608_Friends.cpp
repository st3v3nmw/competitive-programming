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

class union_find {
    public:
        union_find(unsigned int n) {
            parent = vector<unsigned int> (n);
            size = vector<unsigned int> (n, 1);
            for (unsigned int i = 0; i < n; i++)
                parent[i] = i;
        }

        unsigned int find(unsigned int x) {
            if (parent[x] == x)
                return x;
            parent[x] = find(parent[x]);
            return parent[x];
        }

        void unify(unsigned int x, unsigned int y) {
            unsigned int p_x = find(x);
            unsigned int p_y = find(y);

            if (p_x == p_y)
                return; // x and y are already in the same set
            
            parent[p_x] = p_y;
            size[p_y] += size[p_x];
            if (size[p_y] > largest)
                largest = size[p_y];
        }

        bool connected(unsigned int x, unsigned int y) {
            return find(x) == find(y);
        }

    vector<unsigned int> parent, size;
    unsigned int largest = 0;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    unsigned int t, n, m, f1, f2;
    cin >> t;
    for (int d = 0; d < t; d++) {
        cin >> n >> m;
        union_find q(n);
        while (m--) {
            cin >> f1 >> f2;
            q.unify(f1 - 1, f2 - 1);
        }
        cout << q.largest << eol;
    }
}