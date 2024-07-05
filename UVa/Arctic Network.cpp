/**
 * UVa10369
 * 北极通信网络
 * 稠密图适合用prim算法求最小生成树
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

#define N 502
int x[N], y[N], n, s; double d[N], e[N]; bool f[N];

struct node {
    int u; double d;
    bool operator< (const node &rhs) const {
        return d > rhs.d;
    }
} t;

double solve () {
    cin >> s >> n;
    priority_queue<node> q; q.push({0, 0.});
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i], d[i] = 20000., f[i] = false;
    int cc = 1;
    while (!q.empty()) {
        t = q.top(); q.pop(); int u = t.u;
        if (f[u]) continue;
        f[u] = true;
        if (t.d > 0.) e[cc++] = t.d;
        if (cc == n) break;
        for (int v=0; v<n; ++v) if (!f[v]) {
            double s = sqrt((x[u]-x[v])*(x[u]-x[v]) + (y[u]-y[v])*(y[u]-y[v]));
            if (s < d[v]) q.push({v, d[v] = s});
        }
    }
    sort(e+1, e+n);
    return s>1 ? e[n-s] : e[n-1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(2);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
}