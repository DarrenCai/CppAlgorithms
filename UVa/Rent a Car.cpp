/**
 * UVa12433
 * 租车
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 130
struct edge {short u, v, cap, flow; int cost;} e[N*N>>1];
short g[N][N], q[N*N*N], p[N], cnt[N], n, s, r, c; int a[N], d[N]; bool visit[N];

void addEdge(short u, short v, short cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short T; cin >> T;
    for (short kase=1; kase<=T; ++kase) {
        cin >> n >> s >> r;
        short t = 2*n+2; int cc = 0, ff = 0, flow = 0;
        memset(cnt, c = 0, sizeof(cnt));
        for (short i=1; i<=n; ++i) {
            short v; cin >> v; ff += v;
            if (i<n) addEdge(i, i+1, 10000, 0);
            addEdge(0, i, v, 0); addEdge(t-1, i+n, N, 0); addEdge(i+n, t, v, 0);
        }
        for (short i=0, c, p; i<s; ++i) cin >> c >> p, addEdge(0, t-1, c, p);
        for (short i=0; i<r; ++i) {
            short d, s; cin >> d >> s; ++d;
            for (short i=1; i<=n; ++i) if (i+d <= n) addEdge(i, i+d+n, 10000, s);
        }
        while (true) {
            memset(d, 0x3f, sizeof(d)); memset(visit, 0, sizeof(visit)); q[0] = 0; d[0] = 0; a[0] = 10000;
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
            if (d[t] == 0x3f3f3f3f) break;
            cc += d[t]*a[t];
            flow += a[t];
            for (int u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << "Case " << kase << ": ";
        flow == ff ? (cout << cc << endl) : (cout << "impossible" << endl);
    }
    return 0;
}