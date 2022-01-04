/**
 * UVa10054
 * 项链
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 61
#define M 1010
int u[M], v[M], g[N][M], path[M<<1], color[N], cnt[N], c[N], cc, m; bool vis[M];

bool check() {
    for (int i=1; i<N; ++i) if (cnt[i]&1) return false;
    return true;
}

void euler(int u) {
    for (int i=0, j; i<cnt[u]; ++i) if (!vis[j = g[u][i]]) {
        int v = ::u[j]+::v[j]-u;
        vis[j] = true; euler(v);
        path[cc++] = v; path[cc++] = u;
        while (c[u]>0) path[cc++] = u, path[cc++] = u, --c[u];
    }
}

void solve() {
    if (check()) {
        memset(vis, cc = 0, sizeof(vis)); euler(u[0]);
        if (cc == 2*m) {
            for (int i=cc-1; i>0; i-=2) cout << path[i] << ' ' << path[i-1] << endl;
            return;
        }
    }
    cout << "some beads may be lost" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int T; cin >> T;
    for (int kase=1; kase<=T; ++kase) {
        cin >> m; memset(cnt, 0, sizeof(cnt)); memset(c, 0, sizeof(c));
        for (int i=0; i<m; ++i) {
            cin >> u[i] >> v[i];
            u[i] != v[i] ? g[u[i]][cnt[u[i]]++] = g[v[i]][cnt[v[i]]++] = i : ++c[u[i]];
        }
        if (kase>1) cout << endl;
        cout << "Case #" << kase << endl;
        solve();
    }
    return 0;
}