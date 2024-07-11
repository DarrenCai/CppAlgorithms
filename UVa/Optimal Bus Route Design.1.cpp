/**
 * UVa1349/LA3353
 * 最优巴士线路设计
 * Taipei 2005
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 110
struct {int v, w;} g[N][N]; int c[N], dx[N], dy[N], px[N], py[N], vis[N], q[N], clk, d, n;
int slack[N], lx[N], ly[N], INF = 20000; bool s[N], t[N];

bool search() {
    memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy)); d = INF;
    int head = 0, tail = 0;
    for (int i=1; i<=n; ++i) if (px[i] < 0) q[tail++] = i, dx[i] = 0;
    while (head < tail) {
        int u = q[head++];
        if (dx[u] > d) break;
        for (int i=0, v; i<c[u]; ++i) if (dy[v = g[u][i].v] < 0) {
            dy[v] = dx[u] + 1;
            py[v] < 0 ? d = dy[v] : (dx[py[v]] = dy[v] + 1, q[tail++] = py[v]);
        }
    }
    return d != INF;
}

bool dfs(int u) {
    for (int i=0, v; i<c[u]; ++i) if (vis[v = g[u][i].v] != clk && dy[v] == dx[u]+1) {
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

bool match(int i) {
    s[i] = true;
    for (int j=0, v; j<c[i]; ++j) if (!t[v = g[i][j].v]) {
        int d = lx[i] + ly[v] + g[i][j].w;
        if (d == 0) {
            t[v] = true;
            if (!px[v] || match(px[v])) {
                px[v] = i; py[i] = j;
                return true;
            }
        } else slack[v] = min(slack[v], d);
    }
    return false;
}

void km() {
    for (int i=1; i<=n; ++i) px[i] = lx[i] = ly[i] = 0;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) slack[j] = INF;
        while (true) {
            for (int j=1; j<=n; ++j) s[j] = t[j] = false;
            if (match(i)) break;
            int a = INF;
            for (int j=1; j<=n; ++j) if (!t[j]) a = min(a, slack[j]);
            for (int j=1; j<=n; ++j) {
                if (s[j]) lx[j] -= a;
                t[j] ? ly[j] += a : slack[j] -= a;
            }
        }
    }
}

void solve () {
    for (int i=1, v, w; i<=n; ++i) {
        c[i] = 0;
        while (cin >> v && v) cin >> w, g[i][c[i]++] = {v, w};
    }
    if (max_match() != n) {
        cout << 'N' << endl;
        return;
    }
    km();
    int ans = 0;
    for (int i=1; i<=n; ++i) ans += g[i][py[i]].w;
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n) solve();
    return 0;
}