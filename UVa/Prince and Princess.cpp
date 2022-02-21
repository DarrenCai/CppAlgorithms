/**
 * UVa10635
 * 王⼦和公主
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define N 65535
int a[N], x[N], n, p, q, v;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    short t; cin >> t; a[1] = 1;
    for (short kase=1; kase<=t; ++kase) {
        cin >> n >> p >> q; n*=n; ++p; ++q;
        memset(x, 0, n*sizeof(int));
        for (int i=1; i<=p; ++i) cin >> v, x[v] = i;
        int t = 1, ans = 0;;
        for (int i=0; i<q; ++i) {
            cin >> v;
            if (x[v]) {
                int k = upper_bound(a+1, a+t, x[v]) - a;
                a[k < t ? k : t++] = x[v];
                ans = max(ans, k);
            }
        }
        cout << "Case " << kase << ": " << ans << endl;
    }
    return 0;
}