/**
 * p4012 深海机器人问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 260
#define INF 0x3f3f3f3f
struct edge {short u, v; int cap, flow, cost;} e[N<<3];
short g[N][8], q[N*N<<3], p[N], cnt[N], c, s, b, x, y; int d[N], a[N]; bool visit[N];

void addEdge(short u, short v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> s >> b >> y >> x) {
        int t = ++x * ++y + 1, v, cc = 0; memset(cnt, c = 0, sizeof(cnt));
        for (short i=0; i<y; ++i) for (short j=1, k; j<x; ++j)
            cin >> v, k = i*x+j, addEdge(k, k+1, 1, -v), addEdge(k, k+1, INF, 0);
        for (short i=0; i<x; ++i) for (short j=1, k; j<y; ++j)
            cin >> v, k = j*x+i+1, addEdge(k-x, k, 1, -v), addEdge(k-x, k, INF, 0);
        for (short i=0, j, k; i<s; ++i) cin >> v >> j >> k, addEdge(0, j*x+k+1, v, 0);
        for (short i=0, j, k; i<b; ++i) cin >> v >> j >> k, addEdge(j*x+k+1, t, v, 0);
        while (true) {
            memset(d, 0x3f, sizeof(d)); memset(visit, 0, sizeof(visit));
            d[0] = 0; q[0] = 0; a[0] = INF;
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
            if (d[t] >= INF) break;
            cc -= a[t]*d[t];
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << cc << endl;
    }
    return 0;
}