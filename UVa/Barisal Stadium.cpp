/**
 * UVa10641
 * 照亮体育馆
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 32
#define M 1010
bool c[M][N]; int m, n, t, v[N][2], p[M][2], cost[M], d[N][N], s[M][3];

int dp() {
    for (short i=0; i<n; ++i) {
        bool ok = false;
        for (short j=0; j<m; ++j) if (c[j][i]) ok = true;
        if (!ok) return -1;
    }
    memset(d, -1, sizeof(d)); t = 0;
    for (short i=0; i<m; ++i) {
        short i1=n, i2=-1;
        for (short j=0; j<n; ++j) if (c[i][j]) i1 = min(i1, j), i2 = max(i2, j);
        if (i1==0 && i2==n-1) {
            while (c[i][i1]) ++i1; while (c[i][i2]) --i2;
            s[t][0] = cost[i]; s[t][1] = i1; s[t++][2] = i2;
            for (short j=0; j<i1; ++j) for (short k=j; k<i1; ++k)
                d[j][k] = d[j][k]<0 ? cost[i] : min(cost[i], d[j][k]);
            for (short j=i2+1; j<n; ++j) for (short k=j; k<n; ++k)
                d[j][k] = d[j][k]<0 ? cost[i] : min(cost[i], d[j][k]);
        } else {
            for (short j=i1; j<=i2; ++j) for (short k=j; k<=i2; ++k)
                d[j][k] = d[j][k]<0 ? cost[i] : min(cost[i], d[j][k]);
        }
    }
    for (short l=1; l<m; ++l) for (short i=0, j; (j=i+l)<n; ++i) for (short k=i; k<j; ++k)
        d[i][j] = d[i][j]<0 ? d[i][k]+d[k+1][j] : min(d[i][j], d[i][k]+d[k+1][j]);
    int ans = d[0][n-1];
    while (t--) ans = min(s[t][0]+d[s[t][1]][s[t][2]], ans);
    return ans;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) {
        for (short i=0; i<n; ++i) cin >> v[i][0] >> v[i][1];
        cin >> m; for (short i=0; i<m; ++i) cin >> p[i][0] >> p[i][1] >> cost[i];
        for (short i=0; i<m; ++i) for (short j=0; j<n; ++j) {
            int nx = v[j==n-1 ? 0 : j+1][1] - v[j][1], ny = v[j][0] - v[j==n-1 ? 0 : j+1][0];
            int x = p[i][0]-v[j][0], y = p[i][1]-v[j][1];
            if (nx*x + ny*y <= 0) c[i][j] = false;
            else {
                x = p[i][0]-v[j==n-1 ? 0 : j+1][0], y = p[i][1]-v[j==n-1 ? 0 : j+1][1];
                c[i][j] = nx*x + ny*y > 0;
            }
        }
        int ans = dp();
        if (ans < 0) cout << "Impossible." << endl;
        else cout << ans << endl;
    }
    return 0;
}