/**
 * UVa12549/LA6156
 * 机器人警卫
 * SWERC 2012
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 101
#define N 5100
int u[M][M], x, y, n; bool r[M][M], w[M][M];
int g[N][N], c[N], dx[N], dy[N], px[N], py[N], vis[N], q[N], nx, ny, clk, d, INF = N<<1;

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

int max_match() {
    memset(px, -1, sizeof(px)); memset(py, -1, sizeof(py)); memset(vis, -1, sizeof(vis));
    int cc = clk = 0;
    while (search()) {
        ++clk;
        for (int i=0; i<nx; ++i) if (px[i] < 0 && dfs(i)) ++cc;
    }
    return cc;
}

int solve() {
    cin >> y >> x >> n; memset(c, nx = ny = 0, sizeof(c)); memset(r, 0, sizeof(r)); memset(w, 0, sizeof(w));
    for (int i=0, x, y; i<n; ++i) cin >> y >> x, r[y][x] = true;
    cin >> n; for (int i=0, x, y; i<n; ++i) cin >> y >> x, w[y][x] = true;
    for (int i=1; i<=y; ++i) for (int j=1, f=1; j<=x; ++j) {
        if (r[i][j]) {
            if (f) f = 0, ++nx;
            u[i][j] = nx-1;
        } else if (w[i][j]) f = 1;
    }
    for (int i=1; i<=x; ++i) for (int j=1, f=1; j<=y; ++j) {
        if (r[j][i]) {
            if (f) f = 0, ++ny;
            int k = u[j][i]; g[k][c[k]++] = ny-1;
        } else if (w[j][i]) f = true;
    }
    return max_match();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}