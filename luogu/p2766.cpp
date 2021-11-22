/**
 * p2766 最长不降子序列问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1010
struct edge {short u, v, cap, flow, cost;} e[N*N>>2];
short q[N*N*N>>2], a[N], d[N], cnt[N], n; int g[N][N>>1], p[N], c; bool visit[N];

void addEdge(short u, short v, short cap, short cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n) {
        memset(cnt, c = 0, sizeof(cnt));
        short t = 2*n+1, s = 0, s1 = 0, s2 = 0;
        for (short i=1; i<=n; ++i) {
            cin >> a[i]; addEdge(0, i, 1, 0); addEdge(i, i+n, 1, 0); addEdge(i+n, t, 1, 0);
        }
        for (short i=1; i<=n; ++i) for (short j=i+1; j<=n; ++j) if (a[i] <= a[j]) addEdge(i+n, j, 1, -1);
        while (true) {
            memset(d, 1, sizeof(d)); memset(visit, 0, sizeof(visit));
            d[0] = 0; q[0] = 0; p[0] = 0; a[0] = 1;
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
            if (d[t] >= 0) break;
            s = min(s, d[t]);
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        for (int i=0; i<c; ++i) e[i].flow = 0;
        while (true) {
            memset(d, 1, sizeof(d)); memset(visit, 0, sizeof(visit));
            d[0] = 0; q[0] = 0; p[0] = 0; a[0] = 1;
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
            if (d[t] >= 0) break;
            if (d[t] == s) ++s1;
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        for (int i=0; i<c; ++i) e[i].flow = 0;
        e[0].cap = n; e[g[1][1]].cap = n;
        e[6*n-2].cap = n; e[6*n-4].cap = n; e[g[t][cnt[t]-1]^1].cap = n;
        while (true) {
            memset(d, 1, sizeof(d)); memset(visit, 0, sizeof(visit));
            d[0] = 0; q[0] = 0; p[0] = 0; a[0] = 1;
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
            if (d[t] >= 0) break;
            if (d[t] == s) ++s2;
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << 1-s << endl << (s==0 ? n : s1) << endl << (s==0 ? n : s2) << endl;
    }
    return 0;
}