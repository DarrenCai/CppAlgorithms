/**
 * UVa11167
 * 峨眉山猴子
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 302
struct edge {int u, v, cap, flow;} e[N*N];
int g[N][N], q[N], p[N], r[N], d[N], cur[N], cnt[N], num[N], c, m, n, kase = 0; bool vis[N];

void add_edge(int u, int v, int cap) {
    e[c] = {u, v, cap, 0}; g[u][cnt[u]++] = c++; e[c] = {v, u, 0, 0}; g[v][cnt[v]++] = c++;
}

bool bfs(int s, int t) {
    memset(vis, 0, sizeof(vis)); memset(d, 0, sizeof(d)); q[0] = t; d[t] = 0; vis[t] = true;
    int head = 0, tail = 1;
    while (head < tail) {
        int v = q[head++];
        for (int i=0; i<cnt[v]; ++i) {
            const edge& ee = e[g[v][i]^1];
            if (!vis[ee.u] && ee.cap > ee.flow) vis[ee.u] = true, d[ee.u] = d[v] + 1, q[tail++] = ee.u;
        }
    }
    return vis[s];
}

void solve() {
    memset(cnt, c = 0, sizeof(cnt));
    int s = 0, t, x = 0, u = s, cc = 0;
    for (int i=1; i<=n; ++i) {
        int v; cin >> v >> p[i] >> q[i]; cc += v; add_edge(s, i, v); r[x++] = p[i]; r[x++] = q[i];
    }
    sort(r, r+x); x = unique(r, r+x) - r; t = n+x;
    for (int i=1; i<x; ++i) add_edge(i+n, t, m*(r[i]-r[i-1]));
    for (int i=1; i<=n; ++i) for (int j = upper_bound(r, r+x, p[i]) - r; j<x && r[j]<=q[i]; ++j)
        add_edge(i, j+n, r[j]-r[j-1]);
    bfs(s, t); memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    while (d[s] <= t) {
        if (u == t) {
            int a = 60000;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            cc -= a; u = s;
        }
        bool ok = false;
        for (int i=cur[u]; i<cnt[u]; ++i) {
            const edge& ee = e[g[u][i]];
            if (ee.cap > ee.flow && d[u] == d[ee.v] + 1) {
                ok = true; p[ee.v] = g[u][i]; cur[u] = i; u = ee.v;
                break;
            }
        }
        if (!ok) {
            int m = t;
            for (int i=0; i<cnt[u]; ++i) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow) m = min(m, d[ee.v]);
            }
            if (--num[d[u]] == 0) break;
            ++num[d[u] = m + 1]; cur[u] = 0;
            if (u != s) u = e[p[u]].u;
        }
    }
    if (cc == 0) {
        cout << "Case " << ++kase << ": Yes" << endl; memset(d, 0, sizeof(d));
        for (int i=1; i<=n; ++i) {
            for (int j=c=0; j<cnt[i]; ++j) {
                const edge& ee = e[g[i][j]];
                if (ee.flow && ee.v > n) {
                    int a = r[ee.v-n-1], b = r[ee.v-n], &f = d[ee.v-n];
                    if (ee.flow == b-a) {
                        c == 0 || q[c-1] < a ? (p[c] = a, q[c++] = b) : q[c-1] = b;
                    } else if (a+f+ee.flow <= b) {
                        c == 0 || q[c-1] < a+f ? (p[c] = a+f, q[c++] = a+f+ee.flow) : q[c-1] = a+f+ee.flow;
                        f = f+ee.flow < b-a ? f+ee.flow : 0;
                    } else {
                        int d = f+ee.flow-b+a;
                        c == 0 || q[c-1] < a ? (p[c] = a, q[c++] = a+d) : q[c-1] = a+d; p[c] = a+f; q[c++] = b; f = d;
                    }
                }
            }
            cout << c;
            for (int j=0; j<c; ++j) cout << " (" << p[j] << ',' << q[j] << ')';
            cout << endl;
        }
    } else cout << "Case " << ++kase << ": No" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m && n) solve();
    return 0;
}