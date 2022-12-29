/**
 * UVa11388
 * 最大公约数和最小公倍数
 */

#include <iostream>
using namespace std;

void solve() {
    int g, l; cin >> g >> l;
    l % g ? cout << -1 << endl : cout << g << ' ' << l << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}