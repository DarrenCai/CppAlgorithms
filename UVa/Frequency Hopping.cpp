/**
 * UVa11248
 * 网络扩容
 */

#include <iostream>
#include <cstring>
#include <set>
using namespace std;

#define INF 2147483647
#define M 10010
#define N 102
struct edge {int u, v, cap, flow;} e[M<<1];
int g[N][N<<1], q[N], p[N], d[N], cur[N], num[N], cnt[N], c, n, m, f, kase = 0; bool vis[N], is_t[N];

void add_edge(int u, int v, int cap) {
    e[c].u = u; e[c].v = v; e[c].cap = cap; e[c].flow = 0; g[u][cnt[u]++] = c++;
    e[c].u = v; e[c].v = u; e[c].cap = 0; e[c].flow = 0; g[v][cnt[v]++] = c++;
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

int max_flow(int f0 = 0) {
    int flow = f0, s = 1, t = n;
    if (!bfs(s, t)) return f0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=1; i<=n; ++i) ++num[d[i]];
    int u = s;
    while (d[s] < n) {
        if (u == t) {
            int a = INF;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            flow += a; u = s;
            if (flow >= f) return flow;
        }
        int ok = 0;
        for (int i=cur[u]; i<cnt[u]; ++i) {
            const edge& ee = e[g[u][i]];
            if (ee.cap > ee.flow && d[u] == d[ee.v] + 1) {
                ok = 1; p[ee.v] = g[u][i]; cur[u] = i; u = ee.v;
                break;
            }
        }
        if (!ok) {
            int m = n - 1;
            for (int i=0; i<cnt[u]; i++) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow) m = min(m, d[ee.v]);
            }
            if (--num[d[u]] == 0) break;
            ++num[d[u] = m+1]; cur[u] = 0;
            if (u != s) u = e[p[u]].u;
        }
    }
    return flow;
}

struct node {
    int u, v;
    bool operator< (const node& rhs) const {
        return u<rhs.u || (u==rhs.u && v<rhs.v);
    }
};

void solve() {
    memset(cnt, c = 0, sizeof(cnt));
    while (m--) {
        int u, v, cap; cin >> u >> v >> cap; add_edge(u, v, cap);
    }
    cout << "Case " << ++kase << ": ";
    int f0 = max_flow();
    if (f0 < f) {
        bfs(1, n); memcpy(is_t, vis, sizeof(vis)); set<node> s;
        for (int i=0; i<c; ++i) e[i].cap -= e[i].flow;
        for (int i=0; i<c; i+=2) if (is_t[e[i].u] != is_t[e[i].v]) {
            e[i].cap = f;
            for (int j=0; j<c; ++j) e[j].flow = 0;
            if (max_flow(f0) >= f) s.insert({e[i].u, e[i].v});
            e[i].cap = 0;
        }
        if (s.size() > 0) {
            set<node>::iterator it = s.begin();
            cout << "possible option:(" << it->u << ',' << it->v << ')';
            while (++it != s.end()) cout << ",(" << it->u << ',' << it->v << ')';
            cout << endl;
        } else cout << "not possible" << endl;
    } else cout << "possible" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m >> f && n) solve();
    return 0;
}