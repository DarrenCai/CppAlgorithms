/**
 * UVa1349
 * 最优巴士路线设计
 * 解法：由于有解时一定满流,直接建网络求最小费用流即可
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 125
#define INF 15000
struct edge {short u, v, cap, flow, cost;} e[4*N*N];
short a[3*N], d[3*N], cnt[3*N], n; int g[3*N][2*N], q[12*N*N*N], p[3*N]; bool visit[3*N]; int c;

void addEdge(short u, short v, short cap, short cost) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cost; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cost; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) {
        short f = 0, cost = 0; c = 0;
        memset(cnt, 0, sizeof(cnt));
        for (short i=1; i<=n; ++i) {
            short s = 3*i-1, j, cc;
            addEdge(0, s, 1, 0);
            addEdge(s, s+1, 1, 0);
            addEdge(s+2, 1, 1, 0);
            while (cin>>j && j) {
                cin >> cc; j = 3*j-1;
                addEdge(s+1, j, 1, cc);
                addEdge(s+1, j+2, 1, cc);
            }
        }
        while (true) {
            memset(d, 60, sizeof(d)); memset(visit, 0, sizeof(visit));
            d[0] = 0; q[0] = 0; visit[0] = true; p[0] = 0; a[0] = N;
            int head = 0, tail = 1;
            while (head < tail) {
                short u = q[head++]; visit[u] = false;
                for (short i=0; i<cnt[u]; ++i) {
                    const edge& ee = e[g[u][i]];
                    if (ee.cap > ee.flow && d[ee.v] > d[u]+ee.cost) {
                        d[ee.v] = d[u]+ee.cost;
                        p[ee.v] = g[u][i];
                        a[ee.v] = min(a[u], short(ee.cap-ee.flow));
                        if (!visit[ee.v]) visit[q[tail++] = ee.v] = true;
                    }
                }
            }
            if (d[1] >= INF) break;
            cost += d[1]*a[1];
            for (short u=1; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[1];
                if (e[p[u]].u+1 == u && u%3 == 0) ++f;
                e[p[u]^1].flow -= a[1];
            }
        }
        f==n ? cout << cost << endl : cout << 'N' << endl;
    }
    return 0;
}