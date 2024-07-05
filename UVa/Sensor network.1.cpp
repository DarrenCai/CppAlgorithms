/**
 * UVa12275/LA4960
 * SWERC 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 352
struct edge {
    int u, v, w;
    bool operator< (const edge &rhs) const {
        return w < rhs.w;
    }
} e[N*N>>1];
int g[N][N], c[N], f[N], q[N], s[N], m, n; bool vis[N];

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

int solve () {
    cin >> m;
    for (int i=0; i<m; ++i) cin >> e[i].u >> e[i].v >> e[i].w;
    sort(e, e+m);
    for (int i=0; i<n; ++i) f[i] = i, c[i] = 0;
    int ans = 1<<16;
    for (int i=0, cc=1, a=0, b=m; i<m; ++i) {
        int u = e[i].u, v = e[i].v, x = find(u), y = find(v);
        if (x == y) {
            for (int j=0; j<n; ++j) {
                vis[j] = false; s[j] = m;
                for (int k=0; k<c[j]; ++k) if (g[j][k] > a && g[j][k] < b) b = g[j][k];
            }
            int h = 0, t = 1; q[0] = u; vis[u] = true;
            while (h < t) {
                x = q[h++];
                for (int j=0; j<c[x]; ++j) {
                    int k = g[x][j]; const edge &ee = e[k];
                    if (vis[y = ee.u + ee.v - x]) continue;
                    vis[y] = true; s[y] = min(s[x], k); q[t++] = y;
                }
            }
            x = e[s[v]].u; y = e[s[v]].v;
            for (int j=0; j<c[x]; ++j) if (g[x][j] == s[v]) {
                while (++j < c[x]) g[x][j-1] = g[x][j]; --c[x];
                break;
            }
            for (int j=0; j<c[y]; ++j) if (g[y][j] == s[v]) {
                while (++j < c[y]) g[y][j-1] = g[y][j]; --c[y];
                break;
            }
            s[v] == a ? (a = b, b = m) : b = m;
        } else f[x] = y, ++cc;
        g[u][c[u]++] = i; g[v][c[v]++] = i;
        if (cc == n) ans = min(ans, e[i].w - e[a].w);
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n) cout << solve() << endl;
}