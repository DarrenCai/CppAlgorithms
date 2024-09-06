/**
 * UVa1212/LA3487
 * 寡头的竞争
 * Hangzhou 2005
 */

#include <iostream>
#include <cstring>
using namespace std;

#define T 300010
#define N 6002
struct edge {int u, v, cap, flow;} e[34*N];
int g[N][N], q[N], p[N], d[N], cur[N], num[N+1], cnt[N], f[T], c, n; bool vis[N];

void add_edge(int u, int v, int cap) {
    e[c] = {u, v, cap, 0}; g[u][cnt[u]++] = c++; e[c] = {v, u, 0, 0}; g[v][cnt[v]++] = c++;
}

bool bfs(int s, int t) {
    memset(vis, 0, sizeof(vis)); q[0] = t; d[t] = 0; vis[t] = true;
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

int solve() {
    int s = 0, t, u = s, cc = 0; memset(cnt, c = 0, sizeof(cnt)); memset(f, 0, sizeof(f));
    cin >> t;
    for (int i=1; i<=t; ++i) {
        int w; cin >> w; add_edge(s, i, w); cc += w;
        while (cin.peek()==' ') cin >> w, f[w] = i;
    }
    cin >> n; t += n+1;
    for (int i=1; i<=n; ++i) {
        int w; cin >> w; add_edge(t-i, t, w); cc += w;
        while (cin.peek()==' ') {
            cin >> w;
            if (f[w]) add_edge(f[w], t-i, T);
        }
    }
    for (int i=0; i<=t; ++i) d[i] = t+1;
    if (!bfs(s, t)) return 0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    while (d[s] <= t) {
        if (u == t) {
            int a = T;
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
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) {
        cout << "Case " << k << ':' << endl << solve() << endl;
        if (k < t) cout << endl;
    }
    return 0;
}