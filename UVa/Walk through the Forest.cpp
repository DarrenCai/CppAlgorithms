/**
 * UVa10917
 * 林中漫步
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define N 1010
int d[N], f[N], n; vector<int> g[N], w[N];
struct node {
    int d, u;
    bool operator< (const node& rhs) const {
        return d>rhs.d;
    }
};

int dp(int u) {
    if (f[u] >= 0) return f[u];
    f[u] = 0;
    for (int i=g[u].size()-1, v; i>=0; --i) if (d[v = g[u][i]] < d[u]) f[u] += dp(v);
    return f[u];
}

void solve() {
    for (int i=1; i<=n; ++i) g[i].clear(), w[i].clear();
    int m; cin >> m;
    while (m--) {
        int u, v, z; cin >> u >> v >> z;
        g[u].push_back(v); w[u].push_back(z); g[v].push_back(u); w[v].push_back(z);
    }
    memset(d, 0x7f, sizeof(d)); memset(f, 0, sizeof(f));
    d[2] = 0; priority_queue<node> q; q.push({0, 2});
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (f[u]) continue;
        f[u] = 1;
        for (int i=g[u].size()-1, v; i>=0; --i) if (d[v = g[u][i]] > d[u] + w[u][i]) {
            d[v] = d[u] + w[u][i]; q.push({d[v], v});
        }
    }
    memset(f, -1, sizeof(f)); f[2] = 1;
    cout << dp(1) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}