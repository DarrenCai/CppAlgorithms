/**
 * p2756 飞行员配对方案问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 110
struct edge {short u, v, cap, flow;} e[N*N>>1];
short g[N][N], q[N*N*N>>1], p[N], a[N], cnt[N], n, m, c;

void addEdge(short u, short v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cin >> m >> n;
    short t = n+1, u, v;
    memset(cnt, c = 0, sizeof(cnt));
    for (short i=1; i<=m; ++i) addEdge(0, i, 1);
    for (short i=m+1; i<=n; ++i) addEdge(i, t, 1);
    while (cin>>u>>v && u>0) addEdge(u, v, 1);
    short flow = 0;
    while (true) {
        memset(a, 0, sizeof(a)); a[0] = N; q[0] = 0;
        int head = 0, tail = 1;
        while (head < tail) {
            short u = q[head++];
            for (short i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (!a[ee.v] && ee.cap > ee.flow) {
                    p[ee.v] = g[u][i];
                    a[ee.v] = min(a[u], short(ee.cap-ee.flow));
                    q[tail++] = ee.v;
                }
            }
            if (a[t]) break;
        }
        if (!a[t]) break;
        flow += a[t];
        for (short u=t; u!=0; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
        }
    }
    cout << flow << endl;
    for (short u=1; u<=m; ++u) for (short i=0; i<cnt[u]; ++i) if (e[g[u][i]].flow == 1) {
        cout << e[g[u][i]].u << ' ' << e[g[u][i]].v << endl;
        break;
    }
    return 0;
}