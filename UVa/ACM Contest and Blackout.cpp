/**
 * UVa10600
 * ACM竞赛和停电
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 105
int d[N][N], g[N][N], c[N], p[N], m, n; bool f[N*(N-1)>>1];

struct node {
    int u, v, w;
    bool operator< (const node& rhs) const {
        return w < rhs.w;
    }
} s[N*(N-1)>>1];

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

void dfs(int u, int fa, int r, int cc = 0) {
    for (int i=0; i<c[u]; ++i) {
        const node &e = s[g[u][i]]; int v = e.u + e.v - u;
        if (v == fa) continue;
        dfs(v, u, r, d[r][v] = max(cc, e.w));
    }
}

void solve () {
    cin >> n >> m;
    for (int i=0; i<m; ++i) cin >> s[i].u >> s[i].v >> s[i].w, f[i] = false;
    sort(s, s+m);
    int ans = 0, ans2 = 400*N;
    for (int i=1; i<=n; ++i) p[i] = i, c[i] = 0;
    for (int i=0, cc=n; i<m; ++i) {
        int x = find(s[i].u), y = find(s[i].v);
        if (x == y) continue;
        p[x] = y; g[s[i].u][c[s[i].u]++] = g[s[i].v][c[s[i].v]++] = i; f[i] = true; ans += s[i].w;
        if (--cc == 1) break;
    }
    for (int i=1; i<=n; ++i) dfs(i, 0, i);
    for (int i=0; i<m; ++i) if (!f[i]) {
        int u = s[i].u, v = s[i].v, w = s[i].w;
        ans2 = min(ans2, ans + w - d[u][v]);
    }
    cout << ans << ' ' << ans2 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
}