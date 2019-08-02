/**
 * UVa11093
 * 环形跑道
 */

#include <iostream>
using namespace std;

#define N 100005
int p[N], ans; long long s;

int main()
{
    int t, n, q; cin >> t;
    for (int k=1; k<=t; ++k) {
        s = ans = 0; cin >> n;
        for (int i=0; i<n; ++i) cin >> p[i];
        for (int i=0; i<n; ++i) cin >> q, p[i] -= q, s += p[i];
        if (s >= 0) for (int i=0, j; !ans && i<n; ++i) {
            if (p[i] < 0) continue;
            for (j=1, s=p[i]; j<n; ++j) if ((s += p[(i+j)%n]) < 0) break;
            if (j == n) ans = i+1;
            else i += j-1;
        }
        if (ans) cout << "Case " << k << ": Possible from station " << ans << endl;
        else cout << "Case " << k << ": Not possible" << endl;
    }
    return 0;
}