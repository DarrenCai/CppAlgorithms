/**
 * p2764 最小路径覆盖问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 300
#define M 15000
struct edge {short u, v, cap, flow;} e[M];
short g[N][N>>1], q[M*N], p[N], a[N], cnt[N], n, m, c; bool vis[N];

void addEdge(short u, short v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cin >> n >> m;
    short t = 2*n+1, u, v;
    memset(cnt, c = 0, sizeof(cnt));
    for (short i=1; i<=n; ++i) addEdge(0, i, 1), addEdge(i+n, t, 1);
    for (short i=0; i<m; ++i) cin >> u >> v, addEdge(u, v+n, 1);
    while (true) {
        memset(a, 0, sizeof(a)); a[0] = 1; q[0] = 0;
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
        for (short u=t; u!=0; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
        }
    }
    for (short i=1; i<=n; ++i) p[i] = i;
    for (short i=1; i<=n; ++i) for (short j=1; j<cnt[i]; ++j) if (e[g[i][j]].flow == 1) {
        p[i] = e[g[i][j]].v - n;
        break;
    }
    memset(vis, c = 0, sizeof(vis));
    for (short i=1, j; i<=n; ++i) if (!vis[i]) {
        for (j=i; p[j] != j; vis[j]=true, j=p[j]) cout << j << ' ';
        ++c; vis[j] = true; cout << j << endl;
    }
    cout << c << endl;
    return 0;
}