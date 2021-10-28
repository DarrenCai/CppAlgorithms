/**
 * UVa10801
 * 电梯换乘
 */

#include <iostream>
#include <algorithm>
using namespace std;
#define N 500
#define INF 10000000

int w[N][N], s[5][N/5], d[N], c[5], t[5]; bool visit[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n, k;
    while (cin >> n >> k) {
        for (short i=0; i<N; ++i) {
            visit[i] = false;
            d[i] = i<n ? 0 : INF;
            for (short j=0; j<N; ++j) w[i][j] = INF;
        }
        for (short i=0; i<n; ++i) {
            cin >> t[i];
            c[i] = 0;
        }
        for (short i=0, u; i<n; ++i) while (cin >> u) {
            u = n*u + i;
            if (c[i]) {
                short v = s[i][c[i]-1];
                w[u][v] = w[v][u] = min(w[u][v], (u-v)/n*t[i]);
            }
            s[i][c[i]++] = u;
            if (cin.get() != ' ') break;
        }
        for (short i=0; i<n; ++i) for (short j=0; j<n; ++j) if (i!=j) for (short k=0; k<c[i]; ++k) {
            short u = s[i][k], v = u+j-i, p = lower_bound(s[j], s[j]+c[j], v) - s[j];
            if (p >= c[j]) break;
            w[u][v] = w[v][u] = 60;
        }
        for (short i=0; i<N; ++i) {
            int x, m = INF;
            for (short y = 0; y<N; ++y) if (!visit[y] && d[y]<m) m = d[x=y];
            visit[x] = true;
            for (short y=1; y<N; ++y) d[y] = min(d[y], d[x] + w[x][y]);
        }
        int ans = INF;
        for (short i=0; i<n; ++i) ans = min(ans, d[n*k+i]);
        ans < INF ? cout << ans << endl : cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}