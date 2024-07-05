/**
 * UVa1265/LA4848
 * 旅游路线
 * Daejeon 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 5002
struct edge {
    int u, v, w;
    bool operator< (const edge &rhs) const {
        return w > rhs.w;
    }
} e[N*N>>1];
struct {int v, w;} g[N][N]; int f[N], c[N], cc[N], m, n;

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

bool check(int r) {
    int x = 0, y = 200000;
    for (int u=1; u<=n; ++u) if (find(u) == r) for (int i=0; i<c[u]; ++i) {
        int v = g[u][i].v, w = g[u][i].w;
        find(v) == r ? y = min(y, w) : x = max(x, w);
    }
    return y > x;
}

int solve () {
    cin >> n >> m;
    for (int i=1; i<=n; ++i) f[i] = i, c[i] = 0, cc[i] = 1;
    for (int i=0, u, v, w; i<m; ++i)
        cin >> u >> v >> w, g[u][c[u]++] = {v, w}, g[v][c[v]++] = {u, w}, e[i] = {u, v, w}, f[find(u)] = find(v);
    sort(e, e+m);
    int ans = 0, cnt = 0;
    for (int i=1; i<=n; ++i) if (find(i) == i) ++cnt;
    for (int i=1; i<=n; ++i) f[i] = i;
    for (int i=0; i<m; ++i) {
        int x = find(e[i].u), y = find(e[i].v);
        if (x == y) continue;
        f[x] = y; cc[y] += cc[x];
        if (check(y)) ans += cc[y];
        if (++cnt == n) break;
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
}