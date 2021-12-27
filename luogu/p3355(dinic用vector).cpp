/**
 * p3355 骑士共存问题
 */

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define N 40010
struct edge {int u, v; short cap, flow;} e[N<<4];
vector<int> g[N]; int d[N], cur[N], c, n, m; bool f[220][220], vis[N];

void addEdge(int u, int v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u].push_back(c++);
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v].push_back(c++);
}

struct dinic {
    int s, t;
    bool bfs() {
        vector<int> q; memset(vis, 0, sizeof(vis)); q.push_back(s); d[s] = 1; vis[s] = true;
        int head = 0, tail = 1;
        while (head < tail) {
            int u = q[head++], ss = g[u].size();
            for (int i=0; i<ss; ++i) {
                const edge& ee = e[g[u][i]];
                if (!vis[ee.v] && ee.cap > ee.flow) {
                    vis[ee.v] = true;
                    d[ee.v] = d[u] + 1;
                    q.push_back(ee.v), ++tail;
                }
            }
        }
        return vis[t];
    }

    int dfs(int u, int a) {
        if (u==t || a==0) return a;
        int flow = 0, f, ss = g[u].size();
        for (int& i = cur[u]; i<ss; ++i) {
            edge& ee = e[g[u][i]];
            if (d[u]+1 == d[ee.v] && (f = dfs(ee.v, min(a, ee.cap-ee.flow))) > 0) {
                ee.flow += f;
                e[g[u][i]^1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    int maxFlow(int s, int t) {
        int flow = 0; this->s = s; this->t = t;
        while (bfs()) {
            memset(cur, 0, sizeof(cur));
            flow += dfs(s, N);
        }
        return flow;
    }
};

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    dinic s;
    while (cin >> n >> m) {
        int cc = n*n-m, t = n*n+1;
        memset(f, c = 0, sizeof(f)); g[0].clear(); g[t].clear();
        for (int x=1; x<=n; ++x) for (int y=1; y<=n; ++y) g[n*(x-1)+y].clear();
        for (int i=0, x, y; i<m; ++i) cin >> x >> y, f[x][y] = true;
        for (int x=1; x<=n; ++x) for (int y=1; y<=n; ++y) if (!f[x][y]) {
            int u = n*(x-1)+y;
            if ((x&1) == (y&1)) {
                addEdge(0, u, 1);
                if (x>2) {
                    if (y>1) addEdge(u, n*(x-3)+y-1, 1);
                    if (y<n) addEdge(u, n*(x-3)+y+1, 1);
                }
                if (x>1) {
                    if (y>2) addEdge(u, n*(x-2)+y-2, 1);
                    if (y+1<n) addEdge(u, n*(x-2)+y+2, 1);
                }
                if (x<n) {
                    if (y>2) addEdge(u, n*x+y-2, 1);
                    if (y+1<n) addEdge(u, n*x+y+2, 1);
                }
                if (x+1<n) {
                    if (y>1) addEdge(u, n*(x+1)+y-1, 1);
                    if (y<n) addEdge(u, n*(x+1)+y+1, 1);
                }
            } else addEdge(u, t, 1);
        }
        cout << cc - s.maxFlow(0, t) << endl;
    }
    return 0;
}