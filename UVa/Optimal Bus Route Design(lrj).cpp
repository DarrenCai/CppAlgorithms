/**
 * UVa1349
 * 最优巴士路线设计
 * 解法：二分图最小权完美匹配
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 125
#define INF 15000
struct edge {short u, v, cap, flow, cost;} e[2*N*N];
short p[2*N], cnt[2*N], a[2*N], d[2*N], n; int g[2*N][N], q[4*N*N*N]; bool visit[2*N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) {
        short t = (n<<1)+3, flow = 0, cost = 0; int c = 0;
        memset(cnt, 0, sizeof(cnt));
        e[c].u = 0; e[c].v = t-2; e[c].cap = N; e[c].flow = 0; e[c].cost = 0; g[0][cnt[0]++] = c++;
        e[c].u = t-2; e[c].v = 0; e[c].cap = 0; e[c].flow = 0; e[c].cost = 0; g[t-2][cnt[t-2]++] = c++;
        e[c].u = t-1; e[c].v = t; e[c].cap = N; e[c].flow = 0; e[c].cost = 0; g[t-1][cnt[t-1]++] = c++;
        e[c].u = t; e[c].v = t-1; e[c].cap = 0; e[c].flow = 0; e[c].cost = 0; g[t][cnt[t]++] = c++;
        for (short i=1; i<=n; ++i) {
            short s = n+i, j, cc;
            e[c].u = t-2; e[c].v = i; e[c].cap = 1; e[c].flow = 0; e[c].cost = 0; g[t-2][cnt[t-2]++] = c++;
            e[c].u = i; e[c].v = t-2; e[c].cap = 0; e[c].flow = 0; e[c].cost = 0; g[i][cnt[i]++] = c++;
            e[c].u = n+i; e[c].v = t-1; e[c].cap = 1; e[c].flow = 0; e[c].cost = 0; g[n+i][cnt[n+i]++] = c++;
            e[c].u = t-1; e[c].v = n+i; e[c].cap = 0; e[c].flow = 0; e[c].cost = 0; g[t-1][cnt[t-1]++] = c++;
            while (cin>>j && j) {
                cin >> cc; j += n;
                e[c].u = i; e[c].v = j; e[c].cap = 1; e[c].flow = 0; e[c].cost = cc; g[i][cnt[i]++] = c++;
                e[c].u = j; e[c].v = i; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[j][cnt[j]++] = c++;
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
            flow += a[t];
            cost += d[t]*a[t];
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        flow==n ? cout << cost << endl : cout << 'N' << endl;
    }
    return 0;
}