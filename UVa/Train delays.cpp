/**
 * UVa1518
 * 火车延误
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <map>
using namespace std;

#define N 1020
struct {int v, m, t, d; long double p;} g[2*N][N]; int gg[2*N][N], cc[2*N], cnt[2*N], q[2*N], n;
long double d[2*N][60]; bool vis[2*N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << setprecision(10);
    int T; cin >> T;
    while (T--) {
        memset(cc, 0, sizeof(cc)); memset(cnt, 0, sizeof(cnt));
        int c = 0; string s1, s2; cin >> s1 >> s2 >> n; map<string, int> id;
        for (int i=0; i<n; ++i) {
            string s3, s4; int m, t, d; long double p;
            cin >> s3 >> s4 >> m >> t >> p >> d; p /= 100;
            int u = id.count(s3) ? id[s3] : id[s3] = c++;
            int v = id.count(s4) ? id[s4] : id[s4] = c++;
            gg[v][cc[v]++] = u;
            g[u][cnt[u]].v = v; g[u][cnt[u]].m = m; g[u][cnt[u]].t = t; g[u][cnt[u]].d = d; g[u][cnt[u]++].p = p;
        }
        if (!id.count(s1) || !id.count(s2)) {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        long double ans = __DBL_MAX__; int s = id[s1], t = id[s2];
        for (int i=0; i<c; ++i) for (int j=0; j<60; ++j) d[i][j] = i==t ? j : __DBL_MAX__;
        memset(vis, 0, sizeof(vis)); vis[t] = true;
        int head = 0, tail = 0;
        for (int i=0; i<cc[t]; ++i) q[tail++] = gg[t][i];
        while (head < tail) {
            int u = q[head++];
            if (vis[u]) continue;
            vis[u] = true;
            for (int i=0; i<cnt[u]; ++i) {
                int m = g[u][i].m, v = g[u][i].v;
                long double p = g[u][i].p/g[u][i].d, pp = 1-g[u][i].p;
                int t = g[u][i].t + m, r = t%60; long double dd = (t-r + d[v][r])*pp;
                for (int k=1; k<=g[u][i].d; ++k) r = (t+k)%60, dd += (t+k-r + d[v][r])*p;
                for (int j=0; j<=m; ++j) d[u][j] = min(d[u][j], dd);
                dd += 60; for (int j=m+1; j<60; ++j) d[u][j] = min(d[u][j], dd);
            }
            for (int i=0; i<cc[u]; ++i) {
                int v = gg[u][i];
                for (int i=0; i<cnt[v]; ++i) {
                    int m = g[v][i].m, u = g[v][i].v;
                    long double p = g[v][i].p/g[v][i].d, pp = 1-g[v][i].p;
                    int t = g[v][i].t + m, r = t%60; long double dd = (t-r + d[u][r])*pp;
                    for (int k=1; k<=g[v][i].d; ++k) r = (t+k)%60, dd += (t+k-r + d[u][r])*p;
                    for (int j=0; j<=m; ++j) if (dd < d[v][j]) d[v][j] = dd, vis[v] = false;
                    dd += 60; for (int j=m+1; j<60; ++j) if (dd < d[v][j]) d[v][j] = dd, vis[v] = false;
                }
                if (!vis[v]) q[tail++] = v;
            }
        }
        for (int i=0; i<60; ++i) ans = min(ans, d[s][i]-i);
        ans == __DBL_MAX__ ? cout << "IMPOSSIBLE" << endl : cout << ans << endl;
    }
    return 0;
}