/**
 * p3356 火星探险问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define S 40
#define N 3210
struct edge {short u, v, cap, flow; int cost;} e[N<<3];
short s[S][S], g[N][7], q[N*N<<3], a[N], p[N], cnt[N], c, n, x, y, t, tt; int d[N]; bool visit[N];

void addEdge(short u, short v, short cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

void print(short i, short u) {
    for (short j=0; j<cnt[u]; ++j) if (e[g[u][j]].flow > 0) {
        short v = e[g[u][j]].v, uu = u > tt ? u-tt : u;
        if (v == t) return;
        --e[g[u][j]].flow;
        if (v != u+tt) cout << i << ' ' << (x>1 && v==uu+1 ? 1 : 0) << endl;
        print(i, v);
        break;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> x >> y) {
        tt = x*y; t = 2*tt + 1; memset(cnt, c = 0, sizeof(cnt));
        for (short i=0; i<y; ++i) for (short j=0; j<x; ++j) {
            cin >> s[i][j];
            if (s[i][j] == 2) addEdge(i*x+j+1, i*x+j+tt+1, 1, -1);
        }
        addEdge(0, 1, n, 0); addEdge(tt, t, S, 0);
        if (s[x-1][y-1] == 2) addEdge(t-1, t, 1, 0);
        for (short i=0; i<y; ++i) for (short j=1; j<x; ++j) if (s[i][j-1]!=1 && s[i][j]!=1) {
            short k = i*x+j; addEdge(k, k+1, S, 0);
            if (s[i][j-1] == 2) addEdge(k+tt, k+1, 1, 0);
        }
        for (short i=0; i<x; ++i) for (short j=1; j<y; ++j) if (s[j-1][i]!=1 && s[j][i]!=1) {
            short k = j*x+i+1; addEdge(k-x, k, S, 0);
            if (s[j-1][i] == 2) addEdge(k-x+tt, k, 1, 0);
        }
        while (true) {
            memset(d, 0x7f, sizeof(d)); memset(visit, 0, sizeof(visit));
            d[0] = 0; q[0] = 0; a[0] = S;
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
            if (d[t] >= 0x7f7f7f7f) break;
            for (short u=t; u!=0; u=e[p[u]].u) {
                e[p[u]].flow += a[t];
                e[p[u]^1].flow -= a[t];
            }
        }
        for (short i=1; i<=n; ++i) print(i, 1);
    }
    return 0;
}