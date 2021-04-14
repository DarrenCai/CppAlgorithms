/**
 * UVa557
 * 汉堡
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    int t; cin >> t;
    while (t--) {
        int n, p = 0; cin >> n; n = (n>>1) -1;
        double ans = .0, c = 1.;
        for (int i=0; i<n; ++i) {
            if (i) c = c*(n+i)*.25/i;
            if (p && c < 1.e100) c *= 1.e100, ans *= 1.e100, --p;
            if (c > 1.e200) c /= 1.e100, ans /= 1.e100, ++p;
            ans = .5*(ans + c);
        }
        cout << ans << endl;
    }
    return 0;
}