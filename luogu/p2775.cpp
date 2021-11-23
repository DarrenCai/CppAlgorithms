/**
 * p2775 机器人路径规划问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1050
struct edge {short u, v, cap, flow, cost;} e[8*N];
short g0[N][N], g[N][N], q[8*N*N], a[N], p[N], d[N], c0[N], cnt[N], n, s, t, c; bool visit[N], f[N], v[N];

void addEdge(short u, short v, short cap, short cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> s >> t) {
        short f1 = 0, f2 = 0;
        for (short i=0; i<n; ++i) {
            cin >> f[i] >> c0[i]; d[i] = -1; v[i] = false;
            for (short j=0; j<c0[i]; ++j) cin >> g0[i][j];
            f1 += !f[i];
        }
        short head = 0, tail = 1; d[q[0] = s] = 0; p[s] = -1;
        while (head < tail) {
            short u = q[head++], v;
            for (short i=0; i<c0[u]; ++i) if (d[v = g0[u][i]] < 0) d[q[tail++] = v] = d[u]+1, p[v] = u;
        }
        for (short u=t; u >= 0; u=p[u]) v[u] = true;
        for (short i=0; i<n; ++i) f2 += !v[i];
        if (f1 > f2) {
            cout << "No solution！" << endl; continue;
        }
        int ans = d[t]; t = n+1;
        memset(cnt, c = 0, sizeof(cnt));
        for (short i=0; i<n; ++i) {
            if (!f[i]) addEdge(n, i, 1, 0);
            if (!v[i]) addEdge(i, t, 1, 0);
            for (short j=0; j<c0[i]; ++j) addEdge(i, g0[i][j], n, 1);
        }
        while (true) {
            memset(d, 10, sizeof(d)); memset(visit, 0, sizeof(visit));
            d[n] = 0; q[0] = n; a[n] = 1;
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
            if (d[t] > n) break;
            ans += d[t];
            for (short u=t; u!=n; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << ans << endl;
    }
    return 0;
}