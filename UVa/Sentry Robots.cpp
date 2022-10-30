/**
 * UVa12549
 * 机器人警卫
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 5120
struct edge {short u, v, cap, flow;} e[N*N];
short u[N/50][N/50], q[20*N*N], a[N], cnt[N], x, y; int g[N][N], p[N], c; bool r[N/50][N/50], w[N/50][N/50];

void addEdge(short u, short v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        memset(r, 0, sizeof(r)); memset(w, 0, sizeof(w));
        short xi, yi, n;
        cin >> y >> x >> n;
        for (short i=0; i<n; ++i) {
            cin >> yi >> xi;
            r[yi][xi] = true;
        }
        cin >> n;
        for (short i=0; i<n; ++i) {
            cin >> yi >> xi;
            w[yi][xi] = true;
        }
        memset(cnt, c = 0, sizeof(cnt));
        short t = 0, flow = 0;
        for (short i=1; i<=y; ++i) {
            bool f = true;
            for (short j=1; j<=x; ++j) {
                if (r[i][j]) {
                    if (f) f=false, addEdge(0, ++t, 1);
                    u[i][j] = t;
                } else if (w[i][j]) f = true;
            }
        }
        xi = t;
        for (short i=1; i<=x; ++i) {
            bool f = true;
            for (short j=1; j<=y; ++j) {
                if (r[j][i]) {
                    if (f) f=false, ++t;
                    addEdge(u[j][i], t, 1);
                } else if (w[j][i]) f = true;
            }
        }
        for (short i=t++; i>xi; --i) addEdge(i, t, 1);
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
        cout << flow << endl;
    }
    return 0;
}