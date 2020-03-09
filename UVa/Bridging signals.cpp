/**
 * ICPC Archive Volumes :: Volume 29 (2900-2999)
 * Regionals 2003 >> Europe - Northwestern
 * 2931 - Bridging signals
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 40005
int g[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        int n, ans=0; cin >> n;
        for (int i=1; i<=n; ++i) g[i] = N;
        for (int i=0; i<n; ++i) {
            int p; cin >> p;
            int k = lower_bound(g+1, g+1+n, p) - g;
            ans = max(ans, k);
            g[k] = p;
        }
        cout << ans << endl;
    }
    return 0;
}