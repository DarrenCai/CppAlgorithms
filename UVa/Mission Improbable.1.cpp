/**
 * UVa1751/LA8041
 * World Finals 2017
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 101
int g[N][N], c[N], hx[N], hy[N], dx[N], dy[N], px[N], py[N], vis[N], q[N], nx, ny, clk, d, INF = N<<1; bool f[N][N];

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

long long solve() {
    long long cc = 0;
    memset(hx, 0, sizeof(hx)); memset(hy, 0, sizeof(hy));
    for (int i=1, x; i<=nx; ++i) for (int j=1; j<=ny; ++j)
        cin >> x, f[i][j] = x--, hx[i] = max(hx[i], x), hy[j] = max(hy[j], x), cc += max(x, 0);
    for (int i=1; i<=nx; ++i) cc -= hx[i], c[i] = 0;
    for (int i=1; i<=ny; ++i) cc -= hy[i];
    for (int i=1; i<=nx; ++i) for (int j=1; j<=ny; ++j) if (f[i][j] && hx[i] == hy[j]) g[i][c[i]++] = j;
    max_match();
    for (int i=1; i<=nx; ++i) if (px[i] > 0) cc += hx[i];
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> nx >> ny) cout << solve() << endl;
    return 0;
}