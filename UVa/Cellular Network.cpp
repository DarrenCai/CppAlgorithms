/**
 * UVa1456/LA4731
 * 蜂窝网络
 * Seoul 2009
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
using namespace std;

#define N 110
int d[N][N], u[N];

void solve() {
    int n, w; cin >> n >> w;
    for (int i=1; i<=n; ++i) cin >> u[i];
    sort(u+1, u+n+1, greater<int>());
    for (int i=2; i<=n; ++i) u[i] += u[i-1];
    for (int i=n+1-w; i>0; --i) d[1][i] = u[i]*i;
    for (int i=2; i<=w; ++i) for (int j=n+i-w; j>=i; --j) {
        d[i][j] = u[j]*j;
        for (int k=i-1; k<j; ++k) d[i][j] = min(d[i][j], (u[j]-u[k])*j + d[i-1][k]);
    }
    cout << d[w][n]*1./u[n] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}