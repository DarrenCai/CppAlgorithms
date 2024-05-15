/**
 * UVa11419
 * 我是SAM
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1005
int g[N][N], c[N], dx[N], dy[N], px[N], py[N], vis[N], q[N], m, nx, ny, clk, d, INF = N<<1; bool f[N];

bool search() {
    memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy)); d = INF;
    int head = 0, tail = 0;
    for (int i=1; i<=nx; ++i) if (px[i] < 0) q[tail++] = i, dx[i] = 0;
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
        for (int i=1; i<=nx; ++i) if (px[i] < 0 && dfs(i)) ++cc;
    }
    return cc;
}

void dfs2(int u) {
    f[u] = 1;
    for (int i=0, v; i<c[u]; ++i) if (!vis[v = g[u][i]]) {
        vis[v] = 1;
        if (!f[py[v]]) dfs2(py[v]);
    }
}

void solve() {
    memset(c, 0, sizeof(c));
    while (m--) {
        int u, v; cin >> u >> v; g[u][c[u]++] = v;
    }
    cout << max_match();
    memset(f, 0, sizeof(f)); memset(vis, 0, sizeof(vis));
    for (int i=1; i<=nx; ++i) if (px[i] < 0) dfs2(i);
    for (int i=1; i<=nx; ++i) if (!f[i]) cout << " r" << i;
    for (int i=1; i<=ny; ++i) if (vis[i]) cout << " c" << i;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> nx >> ny >> m && (nx || ny || m)) solve();
    return 0;
}