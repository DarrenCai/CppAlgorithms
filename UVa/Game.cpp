/**
 * UVa1657
 * 游戏
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 201
short d[N][N][N], c1[N<<1], c2[N*N], cnt[N][N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    memset(d, 1, sizeof(d));
    memset(cnt, 0, sizeof(cnt));
    for (int n=2; n<N; ++n) {
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));
        for (int i=1; i<n; ++i) for (int j=i+1; j<=n; ++j) ++c1[i+j], ++c2[i*j];
        for (int m=0; m<=100; ++m) for (int i=1; i<n; ++i) for (int j=i+1; j<=n; ++j)
            if (d[n][i][j] > m && (((m&1) && c2[i*j] == 1) || ((~m&1) && c1[i+j] == 1))) {
                --c1[i+j]; --c2[i*j]; ++cnt[n][m];
                d[n][i][j] = m;
            }
    }
    short n, m;
    while (cin >> n >> m) {
        cout << cnt[n][m] << endl;
        if (cnt[n][m]) for (short i=1; i<n; ++i) for (short j=i+1; j<=n; ++j) if (d[n][i][j] == m)
            cout << i << ' ' << j << endl;
    }
}