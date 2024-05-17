/**
 * UVa1324/LA2957
 * 运送超级计算机
 * NEERC 2003
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define M 202
#define N 51
struct edge {int u, v, cap, flow, cost;} e[M<<2]; struct node {int i, j, n;} f[2][N];
int path[N][N], g[N][N*M<<2], q[N], a[N], p[N], d[N], cnt[N], c, k, m, n, s, t; bool vis[N];

void add_edge(int u, int v, int cap, int cc) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; e[c].cost = cc; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; e[c].cost = -cc; g[v][cnt[v]++] = c++;
}

bool cmp(int i, int j) {
    return d[i] < d[j];
}

void print(int m, int t) {
    cout << t << endl;
    int c[] = {0, 0}, z = m;
    for (int i=0; i<m; ++i) f[0][c[0]++] = {p[i], 0, i+1};
    for (int i=0; i<t; ++i) {
        node (&r)[N] = f[i&1], (&x)[N] = f[~i&1]; int &c1 = c[i&1], &c2 = c[~i&1] = 0;
        cout << c1;
        for (int j=0; j<c1; ++j) {
            node &e = r[j];
            cout << ' ' << e.n << ' ' << path[e.i][e.j];
            if (++e.j < d[e.i]) x[c2++] = {e.i, e.j, e.n};
        }
        cout << endl;
        for (int j=0; j<m && z<k; ++j) if (d[p[j]] < t-i) x[c2++] = {p[j], 0, ++z};
    }
}

void solve() {
    memset(cnt, c = 0, sizeof(cnt));
    while (m--) {
        int u, v; cin >> u >> v;
        if (u == s || v == t) {
            add_edge(u, v, 1, 1);
        } else if (v == s || u == t) {
            add_edge(v, u, 1, 1);
        } else add_edge(u, v, 1, 1), add_edge(v, u, 1, 1);
    }
    while (true) {
        memset(d, 1, sizeof(d)); memset(vis, 0, sizeof(vis));
        d[s] = 0; q[0] = s; a[s] = N;
        int head = 0, tail = 1;
        while (head < tail) {
            short u = q[head++]; vis[u] = false;
            for (short i=0; i<cnt[u]; ++i) {
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
        for (short u=t; u!=s; u=e[p[u]].u) {
            e[p[u]].flow += a[t];
            e[p[u]^1].flow -= a[t];
        }
    }
    for (int i=m=0; i<cnt[s]; ++i) if (e[g[s][i]].flow > 0) {
        d[m] = 1; int u = path[m][0] = e[g[s][i]].v;
        while (u != t) for (int j=0; j<cnt[u]; ++j) if (e[g[u][j]].flow > 0) {
            e[g[u][j]].flow = 0; u = path[m][d[m]++] = e[g[u][j]].v; break;
        }
        p[m] = m; ++m;
    }
    sort(p, p+m, cmp);
    for (int i = 0, dd = d[p[0]], kk = 0; ; kk += (d[p[i]] - dd) * i, dd = d[p[i]]) {
        while (i < m && d[p[i]] == dd) ++i;
        if (i==m || (kk + (d[p[i]] - dd) * i) >= k) return print(min(i,k), dd-1 + (k-kk+i-1)/i);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m >> k >> s >> t) solve();
    return 0;
}