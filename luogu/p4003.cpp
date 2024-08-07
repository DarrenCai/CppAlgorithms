/**
 * P4003 [2017国家集训队测试] 无限之环
 */

#include <iostream>
#include <cstring>
using namespace std;

#define T u+d
#define R u+2*d
#define B u+3*d
#define L u+4*d
#define N 10002
struct edge {int u, v, cap, flow, cost;} e[N<<2];
int g[N][2002], q[N*N<<2], a[N], d[N], p[N], cnt[N], c, m, n; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

int solve() {
    int s = 0, t = 5*m*n + 1, b = 0, f = 0, cc = 0; memset(cnt, c = 0, sizeof(cnt));
    for (int i=1, u=1, d=m*n; i<=n; ++i) for (int j=1; j<=m; ++j, ++u) {
        int x; cin >> x;
        if (!x) continue;
        if ((i+j) & 1) {
            add_edge(s, u, 4, 0);
            if (x == 1) ++f, add_edge(u, T, 1, 0), add_edge(T, R, 1, 1), add_edge(T, L, 1, 1), add_edge(T, B, 1, 2);
            if (x == 2) ++f, add_edge(u, R, 1, 0), add_edge(R, T, 1, 1), add_edge(R, B, 1, 1), add_edge(R, L, 1, 2);
            if (x == 4) ++f, add_edge(u, B, 1, 0), add_edge(B, L, 1, 1), add_edge(B, R, 1, 1), add_edge(B, T, 1, 2);
            if (x == 8) ++f, add_edge(u, L, 1, 0), add_edge(L, T, 1, 1), add_edge(L, B, 1, 1), add_edge(L, R, 1, 2);
            if (x == 3) f+=2, add_edge(u, T, 1, 0), add_edge(u, R, 1, 0), add_edge(T, B, 1, 1), add_edge(R, L, 1, 1);
            if (x == 6) f+=2, add_edge(u, B, 1, 0), add_edge(u, R, 1, 0), add_edge(B, T, 1, 1), add_edge(R, L, 1, 1);
            if (x == 9) f+=2, add_edge(u, T, 1, 0), add_edge(u, L, 1, 0), add_edge(T, B, 1, 1), add_edge(L, R, 1, 1);
            if (x == 12) f+=2, add_edge(u, B, 1, 0), add_edge(u, L, 1, 0), add_edge(B, T, 1, 1), add_edge(L, R, 1, 1);
            if (x == 7) f+=3, add_edge(u, T, 1, 0), add_edge(u, R, 1, 0), add_edge(u, B, 1, 0), add_edge(T, L, 1, 1), add_edge(B, L, 1, 1), add_edge(R, L, 1, 2);
            if (x == 11) f+=3, add_edge(u, T, 1, 0), add_edge(u, R, 1, 0), add_edge(u, L, 1, 0), add_edge(R, B, 1, 1), add_edge(L, B, 1, 1), add_edge(T, B, 1, 2);
            if (x == 13) f+=3, add_edge(u, T, 1, 0), add_edge(u, B, 1, 0), add_edge(u, L, 1, 0), add_edge(T, R, 1, 1), add_edge(B, R, 1, 1), add_edge(L, R, 1, 2);
            if (x == 14) f+=3, add_edge(u, R, 1, 0), add_edge(u, B, 1, 0), add_edge(u, L, 1, 0), add_edge(R, T, 1, 1), add_edge(L, T, 1, 1), add_edge(B, T, 1, 2);
            if (x == 5) f+=2, add_edge(u, T, 1, 0), add_edge(u, B, 1, 0);
            if (x == 10) f+=2, add_edge(u, R, 1, 0), add_edge(u, L, 1, 0);
            if (x == 15) f+=4, add_edge(u, T, 1, 0), add_edge(u, R, 1, 0), add_edge(u, B, 1, 0), add_edge(u, L, 1, 0);
            if (i > 1) add_edge(T, B-m, 1, 0);
            if (j > 1) add_edge(L, R-1, 1, 0);
            if (i < n) add_edge(B, T+m, 1, 0);
            if (j < m) add_edge(R, L+1, 1, 0);
        } else {
            add_edge(u, t, 4, 0);
            if (x == 1) ++b, add_edge(T, u, 1, 0), add_edge(R, T, 1, 1), add_edge(L, T, 1, 1), add_edge(B, T, 1, 2);
            if (x == 2) ++b, add_edge(R, u, 1, 0), add_edge(T, R, 1, 1), add_edge(B, R, 1, 1), add_edge(L, R, 1, 2);
            if (x == 4) ++b, add_edge(B, u, 1, 0), add_edge(L, B, 1, 1), add_edge(R, B, 1, 1), add_edge(T, B, 1, 2);
            if (x == 8) ++b, add_edge(L, u, 1, 0), add_edge(T, L, 1, 1), add_edge(B, L, 1, 1), add_edge(R, L, 1, 2);
            if (x == 3) b+=2, add_edge(T, u, 1, 0), add_edge(R, u, 1, 0), add_edge(B, T, 1, 1), add_edge(L, R, 1, 1);
            if (x == 6) b+=2, add_edge(B, u, 1, 0), add_edge(R, u, 1, 0), add_edge(T, B, 1, 1), add_edge(L, R, 1, 1);
            if (x == 9) b+=2, add_edge(T, u, 1, 0), add_edge(L, u, 1, 0), add_edge(B, T, 1, 1), add_edge(R, L, 1, 1);
            if (x == 12) b+=2, add_edge(B, u, 1, 0), add_edge(L, u, 1, 0), add_edge(T, B, 1, 1), add_edge(R, L, 1, 1);
            if (x == 7) b+=3, add_edge(T, u, 1, 0), add_edge(R, u, 1, 0), add_edge(B, u, 1, 0), add_edge(L, T, 1, 1), add_edge(L, B, 1, 1), add_edge(L, R, 1, 2);
            if (x == 11) b+=3, add_edge(T, u, 1, 0), add_edge(R, u, 1, 0), add_edge(L, u, 1, 0), add_edge(B, R, 1, 1), add_edge(B, L, 1, 1), add_edge(B, T, 1, 2);
            if (x == 13) b+=3, add_edge(T, u, 1, 0), add_edge(B, u, 1, 0), add_edge(L, u, 1, 0), add_edge(R, T, 1, 1), add_edge(R, B, 1, 1), add_edge(R, L, 1, 2);
            if (x == 14) b+=3, add_edge(R, u, 1, 0), add_edge(B, u, 1, 0), add_edge(L, u, 1, 0), add_edge(T, R, 1, 1), add_edge(T, L, 1, 1), add_edge(T, B, 1, 2);
            if (x == 5) b+=2, add_edge(T, u, 1, 0), add_edge(B, u, 1, 0);
            if (x == 10) b+=2, add_edge(R, u, 1, 0), add_edge(L, u, 1, 0);
            if (x == 15) b+=4, add_edge(T, u, 1, 0), add_edge(R, u, 1, 0), add_edge(B, u, 1, 0), add_edge(L, u, 1, 0);
        }
    }
    if (b != f) return -1;
    f = 0;
    while (true) {
        memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[s] = 0; q[0] = s; a[s] = N;
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
        if (d[t] >= N) break; 
        f += a[t]; cc += d[t] * a[t];
        for (int u=t; u!=s; u=e[p[u]].u) e[p[u]].flow += a[t], e[p[u]^1].flow -= a[t];
    }
    return f == b ? cc : -1;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}