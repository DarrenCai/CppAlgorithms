/**
 * UVa1349
 * 最优巴士路线设计
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 125
#define INF 15000
struct edge {short u, v, cap, flow, cost;} e[4*N*N];
short a[3*N], d[3*N], cnt[3*N], n; int g[3*N][2*N], q[12*N*N*N], p[3*N]; bool visit[3*N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) {
        short t = 3*(n+1), f = 0, cost = 0; int c = 0;
        memset(cnt, 0, sizeof(cnt));
        e[c].u = 0; e[c].v = 1; e[c].cap = N; e[c].flow = 0; e[c].cost = 0; g[0][cnt[0]++] = c++;
        e[c].u = 1; e[c].v = 0; e[c].cap = 0; e[c].flow = 0; e[c].cost = 0; g[1][cnt[1]++] = c++;
        e[c].u = t-1; e[c].v = t; e[c].cap = N; e[c].flow = 0; e[c].cost = 0; g[t-1][cnt[t-1]++] = c++;
        e[c].u = t; e[c].v = t-1; e[c].cap = 0; e[c].flow = 0; e[c].cost = 0; g[t][cnt[t]++] = c++;
        for (short i=1; i<=n; ++i) {
            short s = 3*i-1, j, cc;
            e[c].u = 1; e[c].v = s; e[c].cap = 1; e[c].flow = 0; e[c].cost = 0; g[1][cnt[1]++] = c++;
            e[c].u = s; e[c].v = 1; e[c].cap = 0; e[c].flow = 0; e[c].cost = 0; g[s][cnt[s]++] = c++;
            e[c].u = s; e[c].v = s+1; e[c].cap = 1; e[c].flow = 0; e[c].cost = 0; g[s][cnt[s]++] = c++;
            e[c].u = s+1; e[c].v = s; e[c].cap = 0; e[c].flow = 0; e[c].cost = 0; g[s+1][cnt[s+1]++] = c++;
            e[c].u = s+2; e[c].v = t-1; e[c].cap = 1; e[c].flow = 0; e[c].cost = 0; g[s+2][cnt[s+2]++] = c++;
            e[c].u = t-1; e[c].v = s+2; e[c].cap = 0; e[c].flow = 0; e[c].cost = 0; g[t-1][cnt[t-1]++] = c++;
            while (cin>>j && j) {
                cin >> cc; j = 3*j-1;
                e[c].u = s+1; e[c].v = j; e[c].cap = 1; e[c].flow = 0; e[c].cost = cc; g[s+1][cnt[s+1]++] = c++;
                e[c].u = j; e[c].v = s+1; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[j][cnt[j]++] = c++;
                e[c].u = s+1; e[c].v = j+2; e[c].cap = 1; e[c].flow = 0; e[c].cost = cc; g[s+1][cnt[s+1]++] = c++;
                e[c].u = j+2; e[c].v = s+1; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[j+2][cnt[j+2]++] = c++;
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
            if (d[t] >= INF) break;
            cost += d[t]*a[t];
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                if (u<t && e[p[u]].u+1 == u && u%3 == 0) ++f;
                e[p[u]^1].flow -= a[t];
            }
        }
        f==n ? cout << cost << endl : cout << 'N' << endl;
    }
    return 0;
}