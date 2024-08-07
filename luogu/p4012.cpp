/**
 * P4012 深海机器人问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 0x7f7f7f7f
#define N 258
struct edge {int u, v, cap, flow, cost;} e[N<<3]; 
int g[N][N], q[N*N<<3], a[N], d[N], p[N], cnt[N], c, A, B, P, Q; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int solve() {
    int s = 0, t = ++P*++Q+1, cc = 0; memset(cnt, c = 0, sizeof(cnt));
    for (int i=0; i<P; ++i) for (int j=1; j<Q; ++j) {
        int u = i*Q+j, x; cin >> x; add_edge(u, u+1, 1, -x); add_edge(u, u+1, INF, 0);
    }
    for (int j=1; j<=Q; ++j) for (int i=1; i<P; ++i) {
        int v = i*Q+j, x; cin >> x; add_edge(v-Q, v, 1, -x); add_edge(v-Q, v, INF, 0);
    }
    while (A--) {
        int k, x, y; cin >> k >> x >> y; add_edge(s, x*Q+y+1, k, 0);
    }
    while (B--) {
        int k, x, y; cin >> k >> x >> y; add_edge(x*Q+y+1, t, k, 0);
    }
    while (true) {
        memset(d, 127, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[s] = 0; q[0] = s; a[s] = INF;
        int head = 0, tail = 1;
        while (head < tail) {
            int u = q[head++]; vis[u] = false;
            for (int i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow && d[ee.v] > d[u]+ee.cost) {
                    d[ee.v] = d[u]+ee.cost;
                    p[ee.v] = g[u][i];
                    a[ee.v] = min(a[u], ee.cap-ee.flow);
                    if (!vis[ee.v]) vis[q[tail++] = ee.v] = true;
                }
            }
        }
        if (d[t] >= INF) break;
        cc -= d[t] * a[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> A >> B >> P >> Q) cout << solve() << endl;
    return 0;
}