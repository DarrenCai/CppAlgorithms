/**
 * UVa11082
 * 矩阵解码
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 444
struct edge {int u, v, cap, flow;} e[N<<2];
int g[N][25], q[N], p[N], d[N], cur[N], num[N], cnt[N], r, c, cc, n; bool vis[N];

void add_edge(int u, int v, int cap) {
    e[cc].u = u; e[cc].v = v; e[cc].cap = cap; e[cc].flow = 0; g[u][cnt[u]++] = cc++;
    e[cc].u = v; e[cc].v = u; e[cc].cap = 0; e[cc].flow = 0; g[v][cnt[v]++] = cc++;
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

void solve() {
    cin >> r >> c; memset(cnt, cc = 0, sizeof(cnt));
    int s = 0, t = r+c+r*c+1;
    for (int i=1; i<=r; ++i) {
        cin >> d[i]; add_edge(0, i, i>1 ? d[i]-d[i-1]-c : d[i]-c);
        for (int j=1; j<=c; ++j) add_edge(i, r + (i-1)*c + j, 19);
    }
    for (int i=1, k=r+r*c; i<=c; ++i) {
        cin >> d[i]; add_edge(k+i, t, i>1 ? d[i]-d[i-1]-r : d[i]-r);
        for (int j=1; j<=r; ++j) add_edge(r + (j-1)*c + i, k+i, 19);
    }
    bfs(s, t);
    memset(num, 0, sizeof(num)); memset(cur, 0, sizeof(cur));
    for (int i=0; i<=t; ++i) ++num[d[i]];
    int u = s;
    while (d[s] <= t) {
        if (u == t) {
            int a = N;
            for (int v=t; v!=s; v = e[p[v]].u) a = min(a, e[p[v]].cap - e[p[v]].flow);
            for (int v=t; v!=s; v = e[p[v]].u) e[p[v]].flow += a, e[p[v]^1].flow -= a;
            u = s;
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
            int m = t;
            for (int i=0; i<cnt[u]; i++) {
                const edge& ee = e[g[u][i]];
                if (ee.cap > ee.flow) m = min(m, d[ee.v]);
            }
            if (--num[d[u]] == 0) break;
            ++num[d[u] = m + 1]; cur[u] = 0;
            if (u != s) u = e[p[u]].u;
        }
    }
    for (int i=1; i<=r; ++i) for (int j=1; j<=c; ++j) {
        cout << e[g[i][j]].flow + 1; j < c ? cout << ' ' : cout << endl;
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Matrix " << k << endl, solve();
    return 0;
}