#include <bits/stdc++.h>
using namespace std;

int main() {
    int k = -1, dx, dy, x, y;
    while (k != 0) {
        cin >> k;
        cin >> dx >> dy;
        for (int i = 0; i < k; i++) {
            cin >> x >> y;
            if (x == dx || y == dy)
                cout << "divisa\n";
            else if (x > dx && y > dy)
                cout << "NE\n";
            else if (x > dx && y < dy)
                cout << "SE\n";
            else if (x < dx && y > dy)
                cout << "NO\n";
            else
                cout << "SO\n";
        }
    }
}