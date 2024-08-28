/**
 * UVa1663/LA3461
 * 净化器
 * Beijing 2005
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1024
int g[N][10], c[N], dx[N], dy[N], px[N], py[N], vis[N], q[N], u[N], m, n, t, clk, d, INF = N<<1;

void add() {
    int x = -1, v = 0;
    for (int i=0; i<n; ++i) {
        char c; cin >> c;
        if (c == '*') x = i;
        else if (c == '1') v |= 1<<i;
    }
    if (!vis[v]) u[t++] = v, vis[v] = 1;
    if (x >= 0 && !vis[v |= 1<< x]) u[t++] = v, vis[v] = 1;
}

bool search() {
    memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy)); d = INF;
    int head = 0, tail = 0;
    for (int i=0; i<t; ++i) if (px[u[i]] < 0) q[tail++] = u[i], dx[u[i]] = 0;
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
        for (int i=0; i<t; ++i) if (px[u[i]] < 0 && dfs(u[i])) ++cc;
    }
    return cc;
}

int solve() {
    memset(vis, t = 0, sizeof(vis)); memset(c, 0, sizeof(c));
    while (m--) add();
    for (int i=0; i<t; ++i) for (int j=0; j<n; ++j) if (vis[u[i]^(1<<j)]) g[u[i]][c[u[i]]++] = u[i]^(1<<j);
    return t - max_match()/2;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m && n) cout << solve() << endl;
    return 0;
}