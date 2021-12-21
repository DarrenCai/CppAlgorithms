/**
 * p4013 数字梯形问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 50
#define N 3000
struct edge {short u, v, cap, flow; int cost;} e[N<<2];
short g[N][M], q[N*N<<2], a[N], p[N], cnt[N], m, n, c; int w[M][M], d[N]; bool visit[N];

void addEdge(short u, short v, short cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int mcmf(short t) {
    int cc = 0;
    while (true) {
        memset(d, 1, sizeof(d)); memset(visit, 0, sizeof(visit));
        d[0] = 0; q[0] = 0; a[0] = 1;
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
        if (d[t] >= 0) return cc;
        cc -= d[t];
        for (short u=t; u!=0; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
        }
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> m >> n) {
        for (short i=0, t=m; i<n; ++i, ++t) for (short j=0; j<t; ++j) cin >> w[i][j];
        short t = (2*m+n-1)*n/2;
        memset(cnt, c = 0, sizeof(cnt));
        for (short i=1; i<=m; ++i) addEdge(0, i+t, 1, -w[0][i-1]);
        for (short i=1, tt=m+1, cc = m+1; i<n; ++i, ++tt) for (short j=0; j<tt; ++j, ++cc) {
            addEdge(cc, cc+t, 1, 0);
            if (j>0) addEdge(cc-tt+t, cc, 1, -w[i][j]);
            if (j+1<tt) addEdge(cc-tt+t+1, cc, 1, -w[i][j]);
        }
        for (short i=m+n-2; i>=0; --i) addEdge(t-i, 1+(t<<1), 1, 0);
        cout << mcmf(1+(t<<1)) << endl;
        memset(cnt, c = 0, sizeof(cnt));
        for (short i=1; i<=m; ++i) addEdge(0, i, 1, -w[0][i-1]);
        for (short i=1, tt=m+1, cc = m+1; i<n; ++i, ++tt) for (short j=0; j<tt; ++j, ++cc) {
            if (j>0) addEdge(cc-tt, cc, 1, -w[i][j]);
            if (j+1<tt) addEdge(cc-tt+1, cc, 1, -w[i][j]);
        }
        for (short i=m+n-2; i>=0; --i) addEdge(t-i, 1+t, M, 0);
        cout << mcmf(1+t) << endl;
        memset(cnt, c = 0, sizeof(cnt));
        for (short i=1; i<=m; ++i) addEdge(0, i, 1, -w[0][i-1]);
        for (short i=1, tt=m+1, cc = m+1; i<n; ++i, ++tt) for (short j=0; j<tt; ++j, ++cc) {
            if (j>0) addEdge(cc-tt, cc, M, -w[i][j]);
            if (j+1<tt) addEdge(cc-tt+1, cc, M, -w[i][j]);
        }
        for (short i=m+n-2; i>=0; --i) addEdge(t-i, 1+t, M, 0);
        cout << mcmf(1+t) << endl;
    }
    return 0;
}