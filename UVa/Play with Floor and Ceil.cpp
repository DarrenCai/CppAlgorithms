/**
 * UVa10673
 * 玩转Floor和Ceil
 */

#include <iostream>
using namespace std;

void solve() {
    int x, k; cin >> x >> k;
    cout << (k - x%k) << ' ' << x%k << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}