/**
 * UVa1500/LA5760
 * 擦数游戏
 * Chengdu 2011
 */

#include <iostream>
using namespace std;

bool solve() {
    int n, a, c = 0, s = 0, x = 0; cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> a; s ^= a;
        a == 1 ? ++c : x = a;
    }
    if (n-c > 1) return c&1 || (s&1)==(n&1);
    if (n == c) return c%3;
    if (c & 1) return c%3 || x>2;
    return (c%3 && x==2) || x&1;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case #" << kase << ": " << (solve() ? "Alice" : "Bob") << endl;
    return 0;
}