/**
 * UVa10735
 * 混合图的欧拉回路
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 600
#define N 102
struct edge {int u, v, cap, flow;} e[M<<1];
int g[N][M], q[M*N<<1], p[M], a[N], d[N], cnt[N], u[M], v[M], h[M], c, m, n; bool vis[M];

void add_edge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

void euler(int x) {
    for (int i=0, j; i<cnt[x]; ++i) if (!vis[j = g[x][i]]) vis[j] = true, euler(u[j]+v[j]-x), p[n++] = x;
}

bool solve() {
    cin >> n >> m; memset(cnt, c = 0, sizeof(cnt)); memset(d, 0, sizeof(d));
    for (int i=0; i<m; ++i) {
        char x; cin >> u[i] >> v[i] >> x; ++d[u[i]]; --d[v[i]]; h[i] = -1;
        if (x == 'U') h[i] = c, add_edge(u[i], v[i], 1);
    }
    int s = 0, t = n+1, f = 0;
    for (int i=1; i<=n; ++i) {
        if (d[i] & 1) return false;
        if (d[i] > 0) add_edge(s, i, d[i]>>1), f += d[i]>>1;
        if (d[i] < 0) add_edge(i, t, -d[i]>>1);
    }
    if (f) {
        while (true) {
            memset(a, 0, sizeof(a)); a[s] = m; q[0] = s;
            int head = 0, tail = 1;
            while (head < tail) {
                int u = q[head++];
                for (int i=0; i<cnt[u]; ++i) {
                    const edge& ee = e[g[u][i]];
                    if (!a[ee.v] && ee.cap > ee.flow) {
                        p[ee.v] = g[u][i];
                        a[ee.v] = min(a[u], ee.cap-ee.flow);
                        q[tail++] = ee.v;
                    }
                }
                if (a[t]) break;
            }
            if (!a[t]) break;
            f -= a[t];
            for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
        }
    }
    if (f) return false;
    memset(cnt, n = 0, sizeof(cnt));
    for (int i=0; i<m; ++i) {
        vis[i] = false; h[i] >= 0 && e[h[i]].flow ? g[v[i]][cnt[v[i]]++] = i : g[u[i]][cnt[u[i]]++] = i;
    }
    euler(1);
    while (n--) cout << p[n] << ' ';
    cout << 1 << endl;
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        if (!solve()) cout << "No euler circuit exist" << endl;
        if (t) cout << endl;
    }
    return 0;
}