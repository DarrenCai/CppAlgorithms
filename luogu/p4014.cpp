/**
 * p4014 分配问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 220
struct edge {short u, v, cap, flow; int cost;} e[N*N>>1];
short g[N][N>>1], q[N*N*N>>1], p[N], cnt[N], n, c; int d[N], a[N]; bool visit[N];

void addEdge(short u, short v, short cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int mcmf(short t) {
    int cc = 0;
    while (true) {
        memset(d, 0x7f, sizeof(d)); memset(visit, 0, sizeof(visit));
        d[0] = 0; q[0] = 0; a[0] = 1;
        int head = 0, tail = 1;
        while (head < tail) {
            short u = q[head++]; visit[u] = false;
            for (short i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow && d[ee.v] > d[u]+ee.cost) {
                    d[ee.v] = d[u]+ee.cost;
                    p[ee.v] = g[u][i];
                    a[ee.v] = min(a[u], ee.cap-ee.flow);
                    if (!visit[ee.v]) visit[q[tail++] = ee.v] = true;
                }
            }
        }
        if (d[t] >= 0x7f7f7f7f) return cc;
        cc += d[t];
        for (short u=t; u!=0; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
        }
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        int t = 2*n+1, v; memset(cnt, c = 0, sizeof(cnt));
        for (short i=1; i<=n; ++i) addEdge(0, i, 1, 0), addEdge(i+n, t, 1, 0);
        for (short i=1; i<=n; ++i) for (short j=1; j<=n; ++j) cin >> v, addEdge(i, n+j, 1, v);
        cout << mcmf(t) << endl;
        for (short i=0; i<c; ++i) e[i].cost *= -1, e[i].flow = 0;
        cout << -mcmf(t) << endl;
    }
    return 0;
}