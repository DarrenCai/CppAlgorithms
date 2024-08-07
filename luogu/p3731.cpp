/**
 * P3731 [HAOI2017] 新型城市化
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define N 10002
int cc[N], dx[N], dy[N], p[N], vis[N], q[N], clk, d, m, n, t; vector<int> g[N];

bool bipartite(int u) {
    for (int i=g[u].size()-1, v; i>=0; --i) {
        if (cc[v = g[u][i]] == cc[u]) return false;
        if (!cc[v]) {
            cc[v] = 3-cc[u];
            if (!bipartite(v)) return false;
        }
    }
    return true;
}

bool search() {
    memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy)); d = N;
    int head = 0, tail = 0;
    for (int i=1; i<=n; ++i) if (cc[i] == 1 && p[i] < 0) q[tail++] = i, dx[i] = 0;
    while (head < tail) {
        int u = q[head++];
        if (dx[u] > d) break;
        for (int i=g[u].size()-1, v; i>=0; --i) if (dy[v = g[u][i]] < 0) {
            dy[v] = dx[u] + 1;
            p[v] < 0 ? d = dy[v] : (dx[p[v]] = dy[v] + 1, q[tail++] = p[v]);
        }
    }
    return d != N;
}

bool dfs(int u) {
    for (int i=g[u].size()-1, v; i>=0; --i) if (vis[v = g[u][i]] != clk && dy[v] == dx[u]+1) {
        vis[v] = clk;
        if (p[v] >= 0 && dy[v] == d) continue;
        if (p[v] < 0 || dfs(p[v])) {
            p[u] = v; p[v] = u;
            return true;
        }
    }
    return false;
}

void max_match() {
    memset(p, -1, sizeof(p)); memset(vis, -1, sizeof(vis));
    for (clk=0; search(); ++clk) for (int i=1; i<=n; ++i) if (cc[i] == 1 && p[i] < 0) dfs(i);
}

int tarjan(int u) {
    int low = dx[u] = ++clk; q[d++] = u;
    for (int i=g[u].size()-1; i>=0; --i) {
        int v = g[u][i];
        if ((cc[u] == 1 && p[u] == v) || (cc[u] == 2 && v != t && p[u] != v)) continue;
        if (!dx[v]) low = min(low, tarjan(v));
        else if (!dy[v]) low = min(low, dx[v]);
    }
    if (low == dx[u]) {
        ++m;
        while (true) {
            dy[q[--d]] = m;
            if (q[d] == u) break;
        }
    }
    return low;
}

void solve() {
    if (m == 0) {
        cout << 0 << endl;
        return;
    }
    t = n+1; memset(cc, 0, sizeof(cc));
    for (int i=0; i<=t; ++i) g[i].clear();
    while (m--) {
        int u, v; cin >> u >> v; g[u].push_back(v); g[v].push_back(u);
    }
    for (int i=1; i<=n; ++i) if (!cc[i]) cc[i] = 1, bipartite(i);
    max_match(); memset(dx, clk = 0, sizeof(dx)); memset(dy, m = d = 0, sizeof(dy));
    for (int i=1; i<=n; ++i)
        if (cc[i] == 1) p[i] > 0 ? g[i].push_back(0) : g[0].push_back(i);
        else p[i] > 0 ? g[t].push_back(i) : g[i].push_back(t);
    for (int i=0; i<=t; ++i) if (!dx[i]) tarjan(i);
    d = 0;
    for (int i=1; i<=n; ++i) if (p[i] > i && dy[i] != dy[p[i]]) ++d;
    cout << d << endl;
    for (int i=1; i<=n; ++i) if (p[i] > i && dy[i] != dy[p[i]]) cout << i << ' ' << p[i] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) solve();
    return 0;
}