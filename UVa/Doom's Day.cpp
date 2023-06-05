/**
 * UVa11774
 * 世界末日
 */

#include <iostream>
#include <algorithm>
using namespace std;

int solve() {
    int m, n; cin >> m >> n;
    return (m+n) / __gcd(m, n);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    for (int kase=1; kase <= t; ++kase) cout << "Case " << kase << ": " << solve() << endl;
    return 0;
}