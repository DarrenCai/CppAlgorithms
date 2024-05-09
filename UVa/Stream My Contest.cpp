/**
 * UVa11865
 * 比赛网络
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 10010
#define N 63
int f[N], w[N], id[N], vis[N], m, n, c; struct edge {int u, v, b, c;} e0[M], e[M];

bool check(int x) {
    memcpy(e, e0, sizeof(e));
    int ans = 0, r = 0, k = n;
    while (true) {
        for (int i=0; i<k; ++i) f[i] = i;
        for (int i=0; i<m; ++i) if (e[i].b >= x && e[i].u != e[i].v) {
            int u = e[i].u, v = e[i].v;
            if (f[v] == v || e[i].c < w[v]) f[v] = u, w[v] = e[i].c;
        }
        int t = w[r] = 0;
        for (int i=0; i<k; ++i) {
            if (i != r && f[i] == i) return false;
            id[i] = vis[i] = -1;
        }
        for (int i=0, v; i<k; ++i) {
            ans += w[i];
            for (v = i; vis[v] != i && id[v] < 0; v = f[v]) vis[v] = i;
            if (id[v] < 0 && v != r) {
                for (int u = f[v]; u != v; u = f[u]) id[u] = t;
                id[v] = t++;
            }
        }
        if (t == 0) break;
        for (int i=0; i<k; ++i) if (id[i] < 0) id[i] = t++;
        for (int i=0; i<m; ++i) if (e[i].b >= x) {
            int u = e[i].u, v = e[i].v;
            e[i].u = id[u]; e[i].v = id[v]; e[i].c -= w[v];
        }
        k = t; r = id[r];
    }
    return ans <= c;
}

void solve() {
    cin >> n >> m >> c;
    int l = 2000000, r = 0;
    for (int i=0; i<m; ++i) {
        cin >> e0[i].u >> e0[i].v >> e0[i].b >> e0[i].c;
        l = min(l, e0[i].b); r = max(r, e0[i].b);
    }
    if (!check(l)) {
        cout << "streaming not possible." << endl;
        return;
    }
    while (l < r) {
        int m = (l+r+1)>>1;
        check(m) ? l = m : r = m-1;
    }
    cout << l << " kbps" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}