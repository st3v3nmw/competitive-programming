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

// int distance(vector<char> bb, int start, int end, char check) {
//     int dist = end - start + 1;
//     for (int i = start; i < end; i++) {
//         if (bb[i] != check)
//             dist -= 1;
//     }
//     return dist;
// }

// int goodString(vector<char> bb, int start, int end, char check) {
//     int r = 0, d1, d2;
//     if (start == end) { // length 1 strings
//         return bb[start] == check;
//     } else if (end - start == 1) {
//         if (bb[start] == check) {
//             return (bb[end] == check + 1) + 1;
//         } else if (bb[end] == check) {
//             return (bb[start] == check + 1) + 1;
//         }
//         return 0;
//     } else {
//         cout << "fsdf" << endl;
//         int mid = start + (end - start) / 2;

//         d1 = distance(bb, start, mid, check) + goodString(bb, mid + 1, end, check + 1);
//         d2 = distance(bb, mid + 1, end, check) + goodString(bb, start, mid, check + 1);

//         debug(_(d1) << _(d2) << _(check) << _(start) << _(mid) << _(end));

//         // if (d1 == mid - start + 1) {
//         //     return d1 + goodString(bb, mid + 1, end, check + 1);
//         // }
//         // else if (d2 == end - mid) {
//         //     return d2 + goodString(bb, start, mid, check + 1);
//         // }
//         // else {
//         //     d1 += goodString(bb, mid + 1, end, check + 1);
//         //     d2 += goodString(bb, start, mid, check + 1);
//         // }


//         // if (distance(bb, start, mid, check) == 0) { // check 1st half
//         //     r += goodString(bb, mid + 1, end, check + 1);
//         // } else if (distance(bb, mid + 1, end, check) == 0) { // check 2nd half
//         //     r += goodString(bb, start, mid, check + 1);
//         // }

//         r = d1 >= d2 ? d1 : d2;
//         // debug(_(start) << _(mid) << _(end));
//     }
//     return r;
// }

// editorial
int calc(const string &s, char c) {
	if (s.size() == 1)
		return s[0] != c;

	int mid = s.size() / 2;
	int cntl = calc(string(s.begin(), s.begin() + mid), c + 1);
	cntl += s.size() / 2 - count(s.begin() + mid, s.end(), c);
	int cntr = calc(string(s.begin() + mid, s.end()), c + 1);
	cntr += s.size() / 2 - count(s.begin(), s.begin() + mid, c);
	return min(cntl, cntr);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    char c;
    int t, n;
    cin >> t;
    string s;

    for (int i = 0; i < t; i++) {
        // cin >> n;
        // vector<char> bb;
        // for (int j = 0; j < n; j++) {
        //     cin >> c;
        //     bb.push_back(c);
        // }
        // debug(_(n - goodString(bb, 0, n - 1, 'a'))); // check if it's a-good

        cin >> n >> s;
        cout << calc(s, 'a') << endl;
    }
}