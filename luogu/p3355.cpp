/**
 * p3355 骑士共存问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 50000
struct edge {int u, v; short cap, flow;} e[N<<4];
static int g[N][N>>1]; int q[N<<12], a[N], p[N], cnt[N], c, n, m; bool f[220][220];

void addEdge(int u, int v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) {
        int cc = n*n-m, t = n*n+1;
        memset(f, 0, sizeof(f)); memset(cnt, c = 0, sizeof(cnt));
        for (int i=0, x, y; i<m; ++i) cin >> x >> y, f[x][y] = true;
        for (int x = 1; x<=n; ++x) for (int y=1; y<=n; ++y) if (!f[x][y]) {
            int u = n*(x-1)+y;
            if ((x&1) == (y&1)) {
                addEdge(0, u, 1);
                if (x>2) {
                    if (y>1) addEdge(u, n*(x-3)+y-1, 1);
                    if (y<n) addEdge(u, n*(x-3)+y+1, 1);
                }
                if (x>1) {
                    if (y>2) addEdge(u, n*(x-2)+y-2, 1);
                    if (y+1<n) addEdge(u, n*(x-2)+y+2, 1);
                }
                if (x<n) {
                    if (y>2) addEdge(u, n*x+y-2, 1);
                    if (y+1<n) addEdge(u, n*x+y+2, 1);
                }
                if (x+1<n) {
                    if (y>1) addEdge(u, n*(x+1)+y-1, 1);
                    if (y<n) addEdge(u, n*(x+1)+y+1, 1);
                }
            } else addEdge(u, t, 1);
        }
        while (true) {
            memset(a, 0, sizeof(a)); a[0] = 1; q[0] = 0;
            int head = 0, tail = 1;
            while (head < tail) {
                int u = q[head++];
                for (short i=0; i<cnt[u]; ++i) {
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
            cc -= a[t];
            for (int u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        cout << cc << endl;
    }
    return 0;
}