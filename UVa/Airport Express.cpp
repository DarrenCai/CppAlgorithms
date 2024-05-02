/**
 * UVa11374
 * 机场快线
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define N 505
int g[N][N<<1], w[N][N<<1], c[N], d1[N], d2[N], p1[N], p2[N], f[N], m, k, n, s, e, kase = 0;
struct node {
    int d, u;
    bool operator< (const node& rhs) const {
        return d>rhs.d;
    }
};

void dijkstra(int s, int (&d)[N], int (&p)[N]) {
    memset(d, 0x3f, sizeof(d)); memset(f, 0, sizeof(f));
    d[s] = 0; priority_queue<node> q; q.push({d[s], s});
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (f[u]) continue;
        f[u] = 1;
        for (int i=0, v; i<c[u]; ++i) if (d[v = g[u][i]] > d[u] + w[u][i]) {
            d[v] = d[u] + w[u][i]; q.push({d[v], v}); p[v] = u;
        }
    }
}

void solve() {
    memset(c, 0, sizeof(c));
    cin >> m;
    for (int i=0; i<m; ++i) {
        int u, v, z; cin >> u >> v >> z;
        g[u][c[u]] = v; w[u][c[u]++] = z; g[v][c[v]] = u; w[v][c[v]++] = z;
    }
    dijkstra(s, d1, p1); dijkstra(e, d2, p2);
    int ans = d1[e], a = -1, b;
    cin >> k;
    for (int i=0; i<k; ++i) {
        int u, v, z; cin >> u >> v >> z;
        if (d1[u] + d2[v] + z < ans) ans = d1[u] + d2[v] + z, a = u, b = v;
        if (d1[v] + d2[u] + z < ans) ans = d1[v] + d2[u] + z, a = v, b = u;
    }
    if (kase++) cout << endl;
    cout << s;
    if (a < 0) {
        int t = 0;
        for (int i=e; i!=s; i=p1[i]) c[t++] = i;
        while (t) cout << ' ' << c[--t];
        cout << endl << "Ticket Not Used" << endl << ans << endl;
    } else {
        int t = 0;
        for (int i=a; i!=s; i=p1[i]) c[t++] = i;
        while (t) cout << ' ' << c[--t];
        for (int i=b; i!=e; i=p2[i]) c[t++] = i;
        for (int i=0; i<t; ++i) cout << ' ' << c[i];
        cout << ' ' << e << endl << a << endl << ans << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> s >> e) solve();
    return 0;
}