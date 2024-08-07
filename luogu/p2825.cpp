/**
 * P2825 游戏
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1252
struct {int r1, r2, c;} r[N]; char s[52][52];
int g[N][N], c[N], dx[N], dy[N], px[N], py[N], vis[N], q[N], nx, ny, clk, d, m, n, INF = N<<1;

bool search() {
    memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy)); d = INF;
    int head = 0, tail = 0;
    for (int i=0; i<nx; ++i) if (px[i] < 0) q[tail++] = i, dx[i] = 0;
    while (head < tail) {
        int u = q[head++];
        if (dx[u] > d) break;
        for (int i=0, v; i<c[u]; ++i) if (dy[v = g[u][i]] < 0) {
            dy[v] = dx[u] + 1;
            py[v] < 0 ? d = dy[v] : (dx[py[v]] = dy[v] + 1, q[tail++] = py[v]);
        }
    }
    return d != INF;
}

bool dfs(int u) {
    for (int i=0, v; i<c[u]; ++i) if (vis[v = g[u][i]] != clk && dy[v] == dx[u]+1) {
        vis[v] = clk;
        if (py[v] >= 0 && dy[v] == d) continue;
        if (py[v] < 0 || dfs(py[v])) {
            px[u] = v; py[v] = u;
            return true;
        }
    }
    return false;
}

int solve() {
    memset(c, nx = ny = 0, sizeof(c)); memset(px, -1, sizeof(px)); memset(py, -1, sizeof(py)); memset(vis, -1, sizeof(vis));
    for (int i=1; i<=n; ++i) cin >> s[i]+1;
    for (int i=1, t; i<=m; ++i) for (int j=t=1; j<=n; ++j) if (s[j][i] == '#' || j == n) {
        if (s[j][i] != '#' || j > t) r[ny++] = {t, s[j][i] == '#' ? j-1 : j, i};
        t = j+1;
    }
    for (int i=1, h; i<=n; ++i) for (int j=h=1, t=0; j<=m; ++j) {
        if (s[i][j] == '*') {
            while (t < ny && r[t].c < j) ++t;
            if (t >= ny || r[t].c > j || r[t].r1 > i) continue;
            while (t < ny && r[t].r2 < i) ++t;
            if (t < ny) g[nx][c[nx]++] = t;
        }
        if (s[i][j] == '#' || j == m) {
            if (s[i][j] != '#' || j > h) ++nx;
            h = j+1;
        }
    }
    int cc = clk = 0;
    while (search()) {
        ++clk;
        for (int i=0; i<nx; ++i) if (px[i] < 0 && dfs(i)) ++cc;
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}