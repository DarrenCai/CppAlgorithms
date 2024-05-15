/**
 * UVa1201/LA3126
 * 出租车
 * NWERC 2004
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 502
struct {short t, x1, y1, x2, y2;} r[N];
int g[N][N], dx[N], dy[N], px[N], py[N], vis[N], q[N], c[N], n, clk, d, INF = N<<1;

bool search() {
    memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy)); d = INF;
    int head = 0, tail = 0;
    for (int i=1; i<=n; ++i) if (px[i] < 0) q[tail++] = i, dx[i] = 0;
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
        for (int i=1; i<=n; ++i) if (px[i] < 0 && dfs(i)) ++cc;
    }
    return cc;
}

void solve() {
    cin >> n;
    for (short i=1; i<=n; ++i) {
        short t; char _; cin >> t >> _ >> r[i].t >> r[i].x1 >> r[i].y1 >> r[i].x2 >> r[i].y2;
        r[i].t += t*60; c[i] = 0;
    }
    for (short i=1; i<=n; ++i) for (int j=1; j<=n; ++j)
        if (r[i].t + abs(r[i].x2-r[i].x1) + abs(r[i].y2-r[i].y1) + abs(r[i].x2-r[j].x1) + 
            abs(r[i].y2-r[j].y1) < r[j].t) g[i][c[i]++] = j;
    cout << n - max_match() << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}