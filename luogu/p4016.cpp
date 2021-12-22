/**
 * p4016 负载平衡问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 110
#define INF 0x3f3f3f3f
struct edge {short u, v; int cap, flow, cost;} e[6*N];
short g[N][N], q[6*N*N], p[N], cnt[N], n, c; int d[N], a[N]; bool visit[N];

void addEdge(short u, short v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        int t = n+1, v, x = 0, cc = 0; memset(cnt, c = 0, sizeof(cnt));
        for (short i=1; i<=n; ++i) cin >> a[i], x += a[i]; x /= n;
        for (short i=1; i<=n; ++i) {
            if (a[i] > x) addEdge(0, i, a[i]-x, 0);
            else if (a[i] < x) addEdge(i, t, x-a[i], 0);
            addEdge(i==1 ? n : i-1, i, INF, 1); addEdge(i, i==1 ? n : i-1, INF, 1);
        }
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
            cc += a[t]*d[t];
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << cc << endl;
    }
    return 0;
}