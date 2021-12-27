/**
 * p3358 最长k可重区间集问题
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define N 1100
struct edge {short u, v, cap, flow; int cost;} e[3*N];
int g[N][N>>1], q[3*N*N], a[N], d[N], p[N], l[N>>1], r[N>>1], cnt[N], c, n, k; bool visit[N];

void addEdge(short u, short v, short cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> k) {
        int t = 2*n+1, cc = 0;
        for (short i=1; i<=n; ++i) cin >> l[i] >> r[i], a[i] = l[i], a[i+n] = r[i];
        sort(a+1, a+t); t = unique(a+1, a+t)-a;
        memset(cnt, c = 0, sizeof(cnt));
        addEdge(0, 1, k, 0); for (short i=1; i<t; ++i) addEdge(i, i+1, N, 0);
        for (short i=1; i<=n; ++i) {
            short u = lower_bound(a+1, a+t, l[i]) - a, v = lower_bound(a+1, a+t, r[i]) - a;
            addEdge(u, v, 1, l[i]-r[i]);
        }
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