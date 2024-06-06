/**
 * UVa1514/LA5903
 * NWERC 2011
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 170000
#define N 502
int id[N][N], g[M][2], c[M], dx[M], dy[M], px[M], py[M], vis[M], q[M], nx, ny, clk, d, m, n, INF = M<<1; char s[N][N];

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

bool solve() {
    cin >> n >> m;
    for (int i = nx = ny = 0; i<n; ++i) {
        cin >> s[i];
        for (int j=0; j<m; ++j) {
            if (s[i][j] == 'W') id[i][j] = ny++;
            else if (s[i][j] == 'B') id[i][j] = nx, c[nx++] = 0, c[nx++] = 0;
        }
    }
    if (nx != ny) return false;
    for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) if (s[i][j] == 'B') {
        int u = id[i][j];
        if (j && s[i][j-1] == 'W') g[u][c[u]++] = id[i][j-1];
        if (j+1<m && s[i][j+1] == 'W') g[u][c[u]++] = id[i][j+1];
        ++ u;
        if (i && s[i-1][j] == 'W') g[u][c[u]++] = id[i-1][j];
        if (i+1<n && s[i+1][j] == 'W') g[u][c[u]++] = id[i+1][j];
    }
    return max_match() == nx;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) cout << (solve() ? "YES" : "NO") << endl;
    return 0;
}