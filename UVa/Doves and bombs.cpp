/**
 * UVa10765
 * 鸽子和炸弹
 */

#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

#define N 10010
int s[N*N>>1][2], bcc[N][N], g[N][N], c[N], t[N], pre[N], bn[N], clk, cc, p, m, n; bool is_cut[N];

int dfs(int u, int fa = -1) {
    int low = pre[u] = ++clk, child = 0;
    for (int i=0, v; i<c[u]; ++i) if (!pre[v = g[u][i]]) {
        s[p][0] = u; s[p++][1] = v; ++child;
        int lowv = dfs(v, u); low = min(low, lowv);
        if (lowv >= pre[u]) {
            t[++cc] = 0; is_cut[u] = 1;
            while (true) {
                int x = s[--p][0], y = s[p][1];
                if (bn[x] != cc) bcc[cc][t[cc]++] = x, bn[x] = cc;
                if (bn[y] != cc) bcc[cc][t[cc]++] = y, bn[y] = cc;
                if (x == u && y == v) break;
            }
        }
    } else if (pre[v] < pre[u] && v != fa) {
        s[p][0] = u; s[p++][1] = v; low = min(low, pre[v]);
    }
    if (fa < 0 && child == 1) is_cut[u] = 0;
    return low;
}

bool cmp(int i, int j) {
    return pre[i] > pre[j] || (pre[i] == pre[j] && i<j);
}

void solve() {
    memset(c, 0, sizeof(c)); memset(pre, clk = 0, sizeof(pre));
    memset(is_cut, 0, sizeof(is_cut)); memset(bn, cc = p = 0, sizeof(bn));
    int u, v;
    while (cin >> u >> v && u >= 0) g[u][c[u]++] = v, g[v][c[v]++] = u;
    for (int u=0; u<n; ++u) if (!pre[u]) dfs(u);
    for (int u=0; u<n; ++u) if (is_cut[u]) {
        set<int> s;
        for (int i=0; i<c[u]; ++i) s.insert(bn[g[u][i]]);
        pre[u] = s.size();
    } else pre[u] = 1;
    for (int u=0; u<n; ++u) t[u] = u;
    sort(t, t+n, cmp);
    for (int i=0; i<m; ++i) cout << t[i] << ' ' << pre[t[i]] << endl;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n >> m && n) solve();
    return 0;
}