/**
 * p3357 最长k可重线段集问题
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

#define N 1100
struct edge {short u, v, cap, flow; int cost;} e[N*N>>1];
int g[N][N>>1], q[N*N*N>>2], a[N], d[N], p[N], l[N>>1], r[N>>1], cnt[N], c, n, k; bool visit[N];

void addEdge(short u, short v, short cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> k) {
        int t = 2*n+2, cc = 0;
        memset(cnt, c = 0, sizeof(cnt)); addEdge(0, t-1, k, 0);
        for (short i=1; i<=n; ++i) {
            long long x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (x1 > x2) x1 += x2, x2 = x1-x2, x1 = x1-x2;
            l[i] = x1; r[i] = x2;
            addEdge(t-1, i, 1, 0); addEdge(i+n, t, 1, 0);
            addEdge(i, i+n, 1, -sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+.5));
        }
        for (short i=1; i<=n; ++i) for (short j=1; j<=n; ++j)
            if (l[j]>=r[i] && j!=i && (r[j]>l[j] || r[i]>l[i] || l[j]>r[i])) addEdge(i+n, j, 1, 0);
        while (true) {
            memset(d, 0x7f, sizeof(d)); memset(visit, 0, sizeof(visit));
            d[0] = 0; q[0] = 0; a[0] = N;
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
            if (d[t] >= 0x7f7f7f7f) break;
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