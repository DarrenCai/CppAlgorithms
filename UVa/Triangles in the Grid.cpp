/**
 * UVa12508
 * 网格中的三角形
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 205

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int *c[N][N];
    for (int m=0; m<N; ++m) for (int n=0; n<N; ++n) {
        const int size = m*n+1;
        c[m][n] = new int[size];
        memset(c[m][n], 0, size*sizeof(int));
    }
    for (int m=1; m<N; ++m) for (int n=1; n<N; ++n) {
        const int s = m*n;
        for (int y=m>>1; y>0; --y) c[m][n][s] += (y<<1)==m ? 2 : 4;
        for (int x=1; x<n; ++x) for (int y=0; y<m; ++y) c[m][n][(m-y)*n+x*y] += y==0 ? 2 : 4;
        for (int x=1; x<=n; ++x) for (int y=0, yy=(x*m+n-1)/n; y<yy; ++y) c[m][n][m*x-n*y] += 4;
    }
    short t; cin >> t;
    while (t--) {
        int m, n, a, b; cin >> m >> n >> a >> b;
        a<<=1; b = min(b<<1, m*n);
        long long cnt = 0;
        for (int i=1; i<=m; ++i) for (int j=1; j<=n; ++j) {
            const int s = i*j;
            if (s < a) continue;
            for (int k=min(b, s); k>=a; --k) cnt += (m-i+1ll)*(n-j+1)*c[i][j][k];
        }
        cout << cnt << endl;
    }
    return 0;
}