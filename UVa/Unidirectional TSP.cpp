/**
 * UVa116
 * 单向TSP
 */

#include <iostream>
using namespace std;

#define M 12
#define N 105
long long d[M][N]={0}; int a[M][N], nex[M][N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int m, n;
    while (cin >> m >> n) {
        for (int i=1; i<=m; ++i) for (int j=1; j<=n; ++j) cin >> a[i][j];
        for (int i=1; i<=m; ++i) d[i][n] = a[i][n];
        for (int j=n-1; j>0; --j) for (int i=1; i<=m; ++i) {
            int r1 = i==1 ? m : i-1, r2 = i==m ? 1 : i+1, r=i;
            if (d[r1][j+1] < d[r][j+1] || (d[r1][j+1] == d[r][j+1] && r1<r)) r = r1;
            if (d[r2][j+1] < d[r][j+1] || (d[r2][j+1] == d[r][j+1] && r2<r)) r = r2;
            d[i][j] = a[i][j] + d[r][j+1]; nex[i][j] = r;
        }
        int s = 1; for (int i=2; i<=m; ++i) if (d[i][1] < d[s][1]) s = i;
        cout << s;
        for (int i=nex[s][1], j=1; j<n; i=nex[i][++j]) cout << ' ' << i;
        cout << endl << d[s][1] << endl;
    }
    return 0;
}