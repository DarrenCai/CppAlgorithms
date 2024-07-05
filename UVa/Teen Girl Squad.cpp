/**
 * UVa11183
 * 广播消息
 */

#include <iostream>
using namespace std;

#define M 40100
#define N 1005
int g[N][N], c[N], f[N], w[N], id[N], vis[N], m, n, ans;
struct edge {int u, v, w;} e[2][M];

bool dmst(int root) {
    ans = 0;
    int k = n, r = 0;
    while (true) {
        for (int i=0; i<k; ++i) f[i] = i;
        for (int i=0; i<m; ++i) {
            int u = e[r][i].u, v = e[r][i].v;
            if (f[v] == v || e[r][i].w < w[v]) f[v] = u, w[v] = e[r][i].w;
        }
        w[root] = 0;
        int t = 0;
        for (int i=0; i<k; ++i) {
            if (i != root && f[i] == i) return false;
            id[i] = vis[i] = -1;
        }
        for (int i=0, v; i<k; ++i) {
            ans += w[i];
            for (v = i; vis[v] != i && id[v] < 0; v = f[v]) vis[v] = i;
            if (id[v] < 0 && v != root) {
                for (int u = f[v]; u != v; u = f[u]) id[u] = t;
                id[v] = t++;
            }
        }
        if (t == 0) return true;
        for (int i=0; i<k; ++i) if (id[i] < 0) id[i] = t++;
        int cc = 0, s = r^1;
        for (int i=0; i<m; ++i) {
            int u = e[r][i].u, v = e[r][i].v;
            if (id[u] != id[v]) e[s][cc++] = {id[u], id[v], e[r][i].w - w[v]};
        }
        m = cc; r = s; k = t; root = id[root];
    }
    return true;
}

void solve () {
    cin >> n >> m;
    for (int i=0; i<m; ++i) cin >> e[0][i].u >> e[0][i].v >> e[0][i].w;
    dmst(0) ? cout << ans << endl : cout << "Possums!" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) {
        cout << "Case #" << k << ": ";
        solve();
    }
}