/**
 * UVa1658
 * 海军上将
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 22200
#define N 2010
#define INF 1000000

struct edge {short u, v, cap, flow, cost;} e[M]; short g[N][N], q[M*N], p[N], cnt[N], a[N], m, n; int d[N]; bool visit[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) {
        short c = 0, t = (n<<1)-1; int cost = 0;
        memset(cnt, 0, sizeof(cnt));
        e[c].u = 0; e[c].v = 1; e[c].cap = 2; e[c].flow = 0; e[c].cost = 0; g[0][cnt[0]++] = c++;
        e[c].u = 1; e[c].v = 0; e[c].cap = 0; e[c].flow = 0; e[c].cost = 0; g[1][cnt[1]++] = c++;
        for (short i=(n-2)<<1; i>0; i-=2) {
            e[c].u = i; e[c].v = i+1; e[c].cap = 1; e[c].flow = 0; e[c].cost = 0; g[i][cnt[i]++] = c++;
            e[c].u = i+1; e[c].v = i; e[c].cap = 0; e[c].flow = 0; e[c].cost = 0; g[i+1][cnt[i+1]++] = c++;
        }
        for (short i=0; i<m; ++i) {
            short u, v, cc; cin >> u >> v >> cc;
            u = u<n ? (u<<1)-1 : (u-1)<<1; v = v==1 ? 1 : (v-1)<<1;
            e[c].u = u; e[c].v = v; e[c].cap = 1; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
            e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
        }
        e[c].u = t-1; e[c].v = t; e[c].cap = 2; e[c].flow = 0; e[c].cost = 0; g[t-1][cnt[t-1]++] = c++;
        e[c].u = t; e[c].v = t-1; e[c].cap = 0; e[c].flow = 0; e[c].cost = 0; g[t][cnt[t]++] = c++;
        while (true) {
            memset(d, 1, sizeof(d)); memset(visit, 0, sizeof(visit));
            d[0] = 0; q[0] = 0; visit[0] = true; p[0] = 0; a[0] = 2;
            int head =0, tail = 1;
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
            if (d[t] >= INF) break;
            cost += d[t]*a[t];
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << cost << endl;
    }
    return 0;
}