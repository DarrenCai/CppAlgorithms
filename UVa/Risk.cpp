/**
 * UVa12264/LA4949
 * Risk游戏
 * NWERC 2010
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 10000
#define N 204
struct edge {int u, v, cap, flow;} e[N*N>>1];
int g[N][N>>1], q[N], p[N], d[N], cur[N], num[N], cnt[N], a[N>>1], c, n; bool vis[N];

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

int max_flow(int s, int t) {
    int flow = 0, u = s;
    if (!bfs(s, t)) return 0;
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    while (d[s] <= t) {
        if (u == t) {
            int a = INF;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            flow += a; u = s;
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
    return flow;
}

void solve() {
    cin >> n; memset(cnt, c = 0, sizeof(cnt));
    for (int i=1; i<=n; ++i) cin >> a[i];
    int s = 0, t = 2*n+1, m = 0, sum = 0;
    for (int i=1; i<=n; ++i) {
        bool f = false; char x;
        for (int j=1; j<=n; ++j) if (cin >> x && x == 'Y') {
            if (a[i]>0 && a[j]==0) f = true;
            if (a[i]>0 && a[j]>0) add_edge(i, j+n, INF);
        }
        if (!a[i]) continue;
        add_edge(i+n, i, a[i]);
        if (f || a[i]>1) add_edge(s, i+n, f ? a[i] : a[i]-1);
        sum += f ? a[i] : a[i]-1;
        if (f) add_edge(i+n, t, 1), ++m;
    }
    int low = 1, high = sum/m;
    while (low < high) {
        int mid = (low+high+1)>>1;
        for (int i=0; i<c; ++i) {
            e[i].flow = 0;
            if (e[i].v == t) e[i].cap = mid;
        }
        max_flow(s, t) == m*mid ? low = mid : high = mid-1;
    }
    cout << high << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}