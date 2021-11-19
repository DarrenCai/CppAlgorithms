/**
 * p2762 太空飞行计划问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 110
#define INF 30000
struct edge {short u, v, cap, flow;} e[N*N>>1];
short g[N][N>>1], q[N*N*N>>1], p[N], a[N], cnt[N], u[N], n, m, c;

void addEdge(short u, short v, short cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cin >> m >> n;
    short t = m+n+1, cc; int tot = 0;
    memset(cnt, c = 0, sizeof(cnt));
    for (short i=1; i<=m; ++i) {
        cin >> cc; addEdge(0, i, cc); tot += cc;
        while (cin.get() == ' ') cin >> cc, addEdge(i, cc+m, INF);
    }
    for (short i=m+1; i<t; ++i) cin >> cc, addEdge(i, t, cc);
    int flow = 0;
    while (true) {
        memset(a, 0, sizeof(a)); a[0] = INF; q[0] = 0;
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
    cc = 0;
    for (short i=1; i<t; ++i) {
        if (i == m+1) cout << endl, cc = 0;
        if (a[i] > 0) {
            if (i <= m) {
                if (cc++) cout << ' ';
                cout << i;
            } else {
                if (cc++) cout << ' ';
                cout << i - m;
            }
        }
    }
    cout << endl << tot - flow << endl;
    return 0;
}