/**
 * UVa11280
 * 飞到弗雷德里顿
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define INF 2000000000
#define N 101
struct node {
    int u, s, d;
    bool operator< (const node& rhs) const {
        return d > rhs.d;
    }
};
int g[N][10*N], w[N][10*N], d[N][N], c[N], m, n, s; char names[N][22], buf[22]; bool f[N][N];

int idx() {
    cin >> buf;
    for (int i=1; i<=n; ++i) if (!strcmp(names[i], buf)) return i;
    return n;
}

void query() {
    cin >> s;
    if (d[n][s = min(s, n)] < INF) {
        cout << "Total cost of flight(s) is $" << d[n][s] << endl;
    } else cout << "No satisfactory flights" << endl;
}

void solve() {
    cin >> n;
    for (int i=1; i<=n; ++i) cin >> names[i], c[i] = 0;
    cin >> m;
    while (m--) {
        int u = idx(), v = idx(), d; cin >> d;
        if (u == v) continue;
        g[u][c[u]] = v; w[u][c[u]++] = d;
    }
    memset(d, 0x7f, sizeof(d)); memset(f, 0, sizeof(f));
    priority_queue<node> q;
    for (int i=0, v; i<c[1]; ++i) if (w[1][i] < d[v = g[1][i]][0]) q.push({v, 0, d[v][0] = w[1][i]});
    while (!q.empty()) {
        const node& t = q.top(); int u = t.u, s = t.s, r = t.d; q.pop();
        if (f[u][s]) continue;
        f[u][s++] = true;
        for (int i=0, v; i<c[u]; ++i) if (w[u][i] + r < d[v = g[u][i]][s]) q.push({v, s, d[v][s] = w[u][i] + r});
    }
    for (int i=1; i<=n; ++i) d[n][i] = min(d[n][i], d[n][i-1]);
    int s; cin >> s;
    while (s--) query();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) {
        if (k > 1) cout << endl;
        cout << "Scenario #" << k << endl;
        solve();
    }
    return 0;
}