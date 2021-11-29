/**
 * p1251 餐巾计划问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 4100
#define INF 20001000
#define M 20000001000ll
struct edge {int u, v, cost; long long cap, flow;} e[6*N];
int g[N][N], q[6*N*N], d[N], p[N], cnt[N], m, n, c, h, b, f, s; long long a[N]; bool visit[N];

void addEdge(int u, int v, long long cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        memset(cnt, c = 0, sizeof(cnt));
        int t = 2*n+1; long long cost = 0;
        for (int i=1; i<=n; ++i) cin >> a[i];
        cin >> h >> m >> f >> b >> s;
        for (int i=1; i<=n; ++i) {
            addEdge(0, i, a[i], 0); addEdge(i+n, t, a[i], 0); addEdge(0, i+n, a[i], h);
            if (i < n) addEdge(i, i+1, M, 0);
            if (i+m <= n) addEdge(i, i+m+n, M, f);
            if (i+b <= n) addEdge(i, i+b+n, M, s);
        }
        while (true) {
            memset(d, 2, sizeof(d)); memset(visit, 0, sizeof(visit)); q[0] = 0; d[0] = 0; a[0] = M;
            int head = 0, tail = 1;
            while (head < tail) {
                int u = q[head++]; visit[u] = false;
                for (int i=0; i<cnt[u]; ++i) {
                    const edge& ee = e[g[u][i]];
                    if (ee.cap > ee.flow && d[ee.v] > d[u]+ee.cost) {
                        d[ee.v] = d[u]+ee.cost;
                        p[ee.v] = g[u][i];
                        a[ee.v] = min(a[u], ee.cap-ee.flow);
                        if (!visit[ee.v]) visit[q[tail++] = ee.v] = true;
                    }
                }
            }
            if (d[t] > INF) break;
            cost += d[t]*a[t];
            for (int u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << cost << endl;
    }
    return 0;
}