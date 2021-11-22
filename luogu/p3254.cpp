/**
 * p3254 圆桌问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 450
struct edge {short u, v, cap, flow;} e[N*N>>1];
short q[N*N*N>>1], a[N], cnt[N], m, n; int g[N][N], p[N], c;

void addEdge(short u, short v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> m >> n) {
        short t = m+n+1, r; int cc = 0, flow = 0;
        memset(cnt, c = 0, sizeof(cnt));
        for (short i=1; i<=m; ++i) cin >> r, addEdge(0, i, r), cc +=r;
        for (short i=1; i<=n; ++i) {
            cin >> r; addEdge(i+m, t, r);
            for (short j=1; j<=m; ++j) addEdge(j, i+m, 1);
        }
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
            flow += a[t];
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        if (flow == cc) {
            cout << 1 << endl;
            for (short i=1; i<=m; ++i) {
                for (short j=1, f=0; j<cnt[i]; ++j) if (e[g[i][j]].flow == 1) {
                    if (f) cout << ' ';
                    cout << e[g[i][j]].v-m;
                    f = 1;
                }
                cout << endl;
            }
        } else cout << 0 << endl;
    }
    return 0;
}