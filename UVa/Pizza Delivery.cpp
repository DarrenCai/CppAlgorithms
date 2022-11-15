/**
 * UVa1628/LA5847
 * 送匹萨
 * Asia Daejeon 2011
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 105
int d[N][N][2][N], p[N], e[N], n;

void solve() {
    cin >> n;
    for (int i=0; i<n; ++i) cin >> p[i];
    for (int i=0; i<n; ++i) cin >> e[i];
    int x = upper_bound(p, p+n, 0) - p, ans = 0;
    if (x == 0) {
        for (int i=0; i<n; ++i) ans += max(0, e[i] - p[i]);
    } else if (x == n) {
        for (int i=0; i<n; ++i) ans += max(0, e[i] + p[i]);
    } else {
        int y = x-1;
        for (int i=0; i<n; ++i) for (int j=n-1; j>=i; --j) {
            d[i][j][0][0] = d[i][j][1][0] = 0;
            for (int k=1, a=min(x,i), b=max(y,j), t=n-b+a; k<t; ++k) {
                d[i][j][0][k] = d[i][j][1][k] = -100000000;
                for (int z=a-1; z>=0 && n-b+z>=k; --z) {
                    d[i][j][0][k] = max(d[i][j][0][k], d[z][j][0][k-1] + e[z] - k*(p[i]-p[z]));
                    d[i][j][1][k] = max(d[i][j][1][k], d[z][j][0][k-1] + e[z] - k*(p[j]-p[z]));
                }
                for (int z=b+1; z<n && n-z+a>=k; ++z) {
                    d[i][j][0][k] = max(d[i][j][0][k], d[i][z][1][k-1] + e[z] - k*(p[z]-p[i]));
                    d[i][j][1][k] = max(d[i][j][1][k], d[i][z][1][k-1] + e[z] - k*(p[z]-p[j]));
                }
            }
        }
        for (int i=x; i<n; ++i) for (int k=n-i+y+1; k>0; --k) ans = max(ans, d[i][i][0][k-1] + e[i] - k*p[i]);
        for (int i=y; i>=0; --i) for (int k=n-x+i+1; k>0; --k) ans = max(ans, d[i][i][0][k-1] + e[i] + k*p[i]);
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}