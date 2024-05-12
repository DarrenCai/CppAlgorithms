#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define N 50050
int dx[N], dy[N], px[N], py[N], vis[N], q[N], nx, ny, clk, d, p, INF = N<<1; vector<int> g[N];

bool search() {
    memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy)); d = INF;
    int head = 0, tail = 0;
    for (int i=1; i<=nx; ++i) if (px[i] < 0) q[tail++] = i, dx[i] = 0;
    while (head < tail) {
        int u = q[head++];
        if (dx[u] > d) break;
        for (int i=g[u].size()-1, v; i>=0; --i) if (dy[v = g[u][i]] < 0) {
            dy[v] = dx[u] + 1;
            py[v] < 0 ? d = dy[v] : (dx[py[v]] = dy[v] + 1, q[tail++] = py[v]);
        }
    }
    return d != INF;
}

bool dfs(int u) {
    for (int i=g[u].size()-1, v; i>=0; --i) if (vis[v = g[u][i]] != clk && dy[v] == dx[u]+1) {
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
    for (int i=1; i<=nx; ++i) g[i].clear();
    while (p--) {
        int u, v; cin >> u >> v; g[u].push_back(v);
    }
    memset(px, -1, sizeof(px)); memset(py, -1, sizeof(py)); memset(vis, -1, sizeof(vis));
    int cc = clk = 0;
    while (search()) {
        ++clk;
        for (int i=1; i<=nx; ++i) if (px[i] < 0 && dfs(i)) ++cc;
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> nx >> ny >> p) cout << max_match() << endl;
    return 0;
}