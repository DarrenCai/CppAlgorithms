/**
 * p2763 试题库问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1050
struct edge {short u, v, cap, flow;} e[42*N];
int g[N][N], p[N], c; short q[42*N*N], a[N], cnt[N], n, k;

void addEdge(short u, short v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> k >> n) {
        memset(cnt, c = 0, sizeof(cnt));
        short t = n+k+1, v, vv; int cc = 0, flow = 0;
        for (short i=1; i<=k; ++i) cin >> v, addEdge(0, i, v), cc += v;
        for (short i=1; i<=n; ++i) {
            addEdge(i+k, t, 1);
            cin >> v; while(v--) cin >> vv, addEdge(vv, i+k, 1);
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
            for (short i=1; i<=k; ++i) {
                cout << i << ':';
                for (short j=1; j<cnt[i]; ++j) if (e[g[i][j]].flow == 1) cout << ' ' << e[g[i][j]].v-k;
                cout << endl;
            }
        } else cout << "No Solution!" << endl;
    }
    return 0;
}