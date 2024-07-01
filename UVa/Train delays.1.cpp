/**
 * UVa1518/LA5909
 * 火车延误
 * NWERC 2011
 */

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#define N 2020
struct node {int v, m, t, p, d;} g[N][N>>1]; char names[N][22];
int c[N], q[N*N>>1], m, n; double d[N][60]; bool f[N], vis[N];

void init(int u) {
    for (int i=0; i<60; ++i) d[u][i] = 1e6, f[u] = false;
}

int idx() {
    cin >> names[n];
    for (int i=0; i<n; ++i) if (!strcmp(names[i], names[n])) return i;
    return init(n), c[n] = vis[n] = 0, n++;
}

bool dfs(int u) {
    if (u == 0) return true;
    if (!vis[u]) {
        vis[u] = true;
        for (int i=0; i<c[u]; ++i) if (dfs(g[u][i].v)) return true;
    }
    return false;
}

void update(int u, int s) {
    for (int i=0; i<60; ++i) d[u][i] = min(d[u][i], (i>s ? s+60-i : s-i) + d[u][s]);
}

void solve() {
    cin >> names[0] >> names[1] >> m; c[0] = c[1] = vis[0] = vis[1] = 0; n = 2;
    while (m--) {
        int u = idx(), v = idx(); node &t = g[v][c[v]++]; t.v = u; cin >> t.m >> t.t >> t.p >> t.d;
    }
    if (!dfs(1)) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    double ans = 1e6; int head = 0, tail = 1; init(0); q[0] = 1;
    for (int i=0; i<60; ++i) d[1][i] = 0.;
    while (head < tail) {
        int u = q[head++]; f[u] = false;
        for (int i=0; i<c[u]; ++i) {
            const node &t = g[u][i]; double v = 0.;
            if (t.p < 100) v += (1.-t.p/100.) * (t.t + d[u][(t.m+t.t) % 60]);
            if (t.p) {
                double p = t.p/100./t.d;
                for (int j=t.d; j>0; --j) v += p * (t.t+j + d[u][(t.m+t.t+j) % 60]);
            }
            if (v < d[t.v][t.m]) {
                d[t.v][t.m] = v; update(t.v, t.m);
                if (t.v == 0) ans = min(ans, v);
                if (!f[t.v]) f[t.v] = true, q[tail++] = t.v;
            }
        }
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << setprecision(10);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}