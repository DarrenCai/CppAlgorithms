/**
 * UVa12168/LA4288
 * 猫和狗
 * NWERC 2008
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 502
struct {
    struct pet {
        int i; bool c;
        bool operator== (const pet &rhs) const {
            return c==rhs.c && i==rhs.i; 
        }
    } a, b;
} v[N];
int g[N][N], c[N], dx[N], dy[N], px[N], py[N], vis[N], q[N], clk, b, d, n, INF = N<<1;

bool search() {
    memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy)); d = INF;
    int head = 0, tail = 0;
    for (int i=0; i<n; ++i) if (px[i] < 0) q[tail++] = i, dx[i] = 0;
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
        for (int i=0; i<n; ++i) if (px[i] < 0 && dfs(i)) ++cc;
    }
    return cc;
}

int solve () {
    cin >> b >> d >> n;
    for (int i=0; i<n; ++i) {
        c[i] = 0;
        char c1, c2; int j, k; cin >> c1 >> j >> c2 >> k;
        v[i] = {{j, c1=='C'}, {k, c2=='C'}};
    }
    for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j)
        if (v[i].a == v[j].b || v[i].b == v[j].a) g[i][c[i]++] = j, g[j][c[j]++] = i;
    return n - max_match()/2;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}