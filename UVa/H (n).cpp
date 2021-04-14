/**
 * UVa11526
 * H(n)
 */

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n > 0) {
            int m = sqrt(n), p=n; long long ans = n;
            for (int i=2, v; i<=m; ++i, p=v) {
                v = n/i;
                ans += v + (i-1)*(p-v);
            }
            if (n/m > m) ans += m*(p-m);
            cout << ans << endl;
        } else cout << 0 << endl;
    }
    return 0;
}