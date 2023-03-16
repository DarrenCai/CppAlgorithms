/**
 * UVa11892
 * 类Nim游戏
 */

#include <iostream>
using namespace std;

bool solve() {
    int n, f = 0; cin >> n;
    for (int i=0; i<n; ++i) {
        int x; cin >> x;
        if (x > 1) f = 1;
    }
    return n&1 || f;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << (solve() ? "poopi" : "piloop") << endl;
    return 0;
}