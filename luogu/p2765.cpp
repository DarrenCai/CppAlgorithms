/**
 * P2765 魔术球问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 56
#define N 6060
struct edge {int u, v, cap, flow;} e[11*N];
int q[6*N*N], a[N], cnt[N], t = (M-1)*(M-1); int g[N][N>>1], p[N], m[M] = {0}, c; bool vis[N];

void addEdge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

void print(int n, int i, bool f = true) {
    if (i<=m[n] && !vis[i]) {
        if (!f) cout << ' '; cout << i; vis[i] = true;
        if (p[i]<=m[n] && i<=n*n/2) print(n, p[i], false);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    memset(cnt, c = 0, sizeof(cnt));
    for (int i=1; i<t; ++i) {
        if ((i<<1) <= t) addEdge(0, i, 1);
        addEdge(i+t, t, 1);
    }
    for (int i=1; i<M; ++i) for (int v=i*i, m=v>>1, j=m+1, k; j<v; ++j) if ((k = v-j) < v) addEdge(k, j+t, 1);
    while (true) {
        memset(a, 0, sizeof(a)); a[0] = 1; q[0] = 0;
        int head = 0, tail = 1;
        while (head < tail) {
            int u = q[head++];
            for (int i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (!a[ee.v] && ee.cap > ee.flow) {
                    p[ee.v] = g[u][i];
                    a[ee.v] = min(a[u], int(ee.cap-ee.flow));
                    q[tail++] = ee.v;
                }
            }
            if (a[t]) break;
        }
        if (!a[t]) break;
        for (int u=t; u!=0; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
        }
    }
    m[1] = 1;
    for (int i=2; i<M; ++i) for (int v=i*i, c=m[i-1]-i+1, u=v>>1; u>=c; --u)
        for (int j=1; j<cnt[u]; ++j) if (e[g[u][j]].flow == 1) {
            p[u] = e[g[u][j]].v - t;
            if (p[u]+u == v) m[i] = max(m[i], p[u]);
            break;
        }
    int n;
    while (cin>>n) {
        memset(vis, 0, sizeof(vis));
        cout << m[n] << endl;
        for (int i=1; i<=m[n]; ++i) if (!vis[i]) print(n, i), cout << endl;
    }
    return 0;
}