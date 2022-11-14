/**
 * UVa12105/LA3782
 * 越大越好
 * Xi'an 2006
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 110
#define M 3010
int c[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}, b[M][N], d[M][N], n, m, kase = 0;

void solve() {
    memset(d, -1, sizeof(d)); memset(d[0], 0, sizeof(d[0]));
    for (int i=1; i<=n; ++i) for (int j=0; j<m; ++j) for (int k=9; k>=0; --k) if (c[k] <= i) {
        short t = d[(10*j+k)%m][i-c[k]];
        if (t >= 0 && t+1 > d[j][i]) d[j][i] = t+1, b[j][i] = k;
    }
    cout << "Case " << ++kase << ": ";
    if (d[0][n] > 0) {
        while (!b[0][n] && d[0][n]>1) n -= c[0];
        for (int j=0, k; d[j][n]; n-=c[k], j=(10*j+k)%m) cout << (k = b[j][n]);
    } else cout << -1;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n>>m && n) solve();
    return 0;
}