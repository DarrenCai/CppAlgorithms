/**
 * P2761 软件补丁问题
 * 同UVa658 It’s not a Bug, it’s a Feature!
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define T 1050000
#define M 100
#define N 20
struct edge {int u, v, cap, flow, cost;}; vector<edge> e; vector<int> g[T];
int a[T], d[T], p[T], w[M], m, n; bool vis[T]; char s1[M][N+1], s2[M][N+1];

void add_edge(int u, int v, int cap, int cc) {
    g[u].push_back(e.size()); e.push_back({u, v, cap, 0, cc});
    g[v].push_back(e.size()); e.push_back({v, u, 0, 0, -cc});
}

bool check(int u, const char (&s)[N+1]) {
    for (int i=0; i<n; ++i) if ((s[i]=='+' && ~u&(1<<i)) || (s[i]=='-' && u&(1<<i))) return false;
    return true;
}

int state(int u, const char (&s)[N+1]) {
    int v = u;
    for (int i=0; i<n; ++i) {
        if (s[i]=='+') v |= 1<<i;
        else if (s[i]=='-') v ^= v&(1<<i);
    }
    return v;
}

int solve() {
    for (int i=0; i<m; ++i) cin >> w[i] >> s1[i] >> s2[i];
    e.clear(); memset(vis, 0, sizeof(vis));
    int t = 1<<n, s = t-1; g[s].clear(); g[t].clear();
    queue<int> q; q.push(s); vis[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i=0; i<m; ++i) if (check(u, s1[i])) {
            int v = state(u, s2[i]);
            if (!vis[v]) g[v].clear(), q.push(v), vis[v] = true;
            add_edge(u, v, 1, w[i]);
        }
    }
    if (!vis[0]) return 0;
    add_edge(0, t, 1, 0); memset(d, 0x7f, sizeof(d)); memset(vis, 0, sizeof(vis)); d[s] = 0; a[s] = 1; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop(); vis[u] = false;
        for (int i=g[u].size()-1; i>=0; --i) {
            const edge& ee = e[g[u][i]];
            if (ee.cap > ee.flow && d[ee.v] > d[u]+ee.cost) {
                d[ee.v] = d[u]+ee.cost;
                p[ee.v] = g[u][i];
                a[ee.v] = min(a[u], ee.cap-ee.flow);
                if (!vis[ee.v]) vis[ee.v] = true, q.push(ee.v);
            }
        }
    }
    return d[t];
}

int main() {
    freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}