/**
 * UVa1376/LA3661
 * 动物园大逃亡
 * Beijing 2006
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define N 1002
int d[2*N*N], f[2*N*N], m, n, kase = 0; struct edge {int v, w;}; vector<edge> g[2*N*N];
struct node {
    int d, u;
    bool operator< (const node& rhs) const {
        return d>rhs.d;
    }
};

void solve() {
    int t = 2*(m-1)*(n-1)+1;
    for (int i=0; i<=t; ++i) g[i].clear();
    for (int i=0; i<n; ++i) for (int j=1; j<m; ++j) {
        int u = i<n-1 ? 2*(i*(m-1)+j) : t, v = i ? 2*((i-1)*(m-1)+j)-1 : 0, w; cin >> w;
        g[u].push_back({v, w}); g[v].push_back({u, w});
    }
    for (int i=1; i<n; ++i) for (int j=0; j<m; ++j) {
        int u = j ? 2*((i-1)*(m-1)+j) : t, v = j<m-1 ? 2*((i-1)*(m-1)+j)+1 : 0, w; cin >> w;
        g[u].push_back({v, w}); g[v].push_back({u, w});
    }
    for (int i=1; i<n; ++i) for (int j=1; j<m; ++j) {
        int u = 2*((i-1)*(m-1)+j), v = u-1, w; cin >> w;
        g[u].push_back({v, w}); g[v].push_back({u, w});
    }
    memset(d, 0x7f, sizeof(d)); memset(f, 0, sizeof(f));
    d[0] = 0; priority_queue<node> q; q.push({0, 0});
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (u == t) break;
        if (f[u]) continue;
        f[u] = 1;
        for (int i=g[u].size()-1; i>=0; --i) {
            int v = g[u][i].v, d1 = d[u] + g[u][i].w;
            if (d[v] > d1) d[v] = d1, q.push({d[v], v});
        }
    }
    cout << "Case " << ++kase << ": Minimum = " << d[t] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m && (n || m)) solve();
    return 0;
}