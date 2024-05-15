/**
 * UVa12083/LA3415
 * 保守的老师
 * NWERC 2005
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 102
#define N 502
struct stu {int h; char m[M], s[M];} sx[N], sy[N]; char e, mu[M], s[M];
int g[N][N], c[N], dx[N], dy[N], px[N], py[N], vis[N], q[N], m, nx, ny, clk, d, h, INF = N<<1; bool f[N];

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

void add() {
    cin >> h >> e >> mu >> s;
    stu &r = e=='F' ? sx[++nx] : sy[++ny];
    r.h = h; memcpy(r.m, mu, sizeof(mu)); memcpy(r.s, s, sizeof(s));
}

bool check(const stu &a, const stu &b) {
    return abs(a.h-b.h) <= 40 && !strcmp(a.m, b.m) && strcmp(a.s, b.s);
}

void solve() {
    cin >> m;
    memset(c, nx = ny = 0, sizeof(c));
    while (m--) add();
    for (int i=1; i<=nx; ++i) for (int j=1; j<=ny; ++j) if (check(sx[i], sy[j])) g[i][c[i]++] = j;
    cout << nx + ny - max_match() << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}