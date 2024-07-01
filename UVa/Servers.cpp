/**
 * UVa1311/LA2666
 * CERC/SWERC 2002
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

#define N 30010
int g[N][10], w[N][10], a[N], c[N], r[N], d[N], p[N], e[N], m, n; bool f[N];
struct node {
    int u, d;
    bool operator< (const node& rhs) const {
        return d > rhs.d;
    }
};

bool cmp(int i, int j) {
    return r[i] > r[j];
}

int solve() {
    cin >> n >> m;
    for (int i=0; i<n; ++i) cin >> r[i], c[a[i] = i] = 0, e[i] = 33686018;
    while (m--) {
        int u, v, x; cin >> u >> v >> x; --u; --v; g[u][c[u]] = v; g[v][c[v]] = u; w[u][c[u]++] = w[v][c[v]++] = x;
    }
    sort(a, a+n, cmp);
    if (r[a[0]] == r[a[n-1]]) return n*n;
    priority_queue<node> q; int ans = 0;
    for (int i=0; i<n; ++i) {
        memset(d, 2, sizeof(d)); memset(f, 0, sizeof(f)); q.push({a[i], 0});
        if (i==0 || r[a[i]] < r[a[i-1]]) memcpy(p, e, sizeof(p));
        while (!q.empty()) {
            int u = q.top().u, d0 = q.top().d; q.pop();
            if (f[u]) continue;
            f[u] = true; e[u] = min(e[u], d0); ++ans;
            for (int j=0, v, d1; j<c[u]; ++j) if ((d1 = d0 + w[u][j]) < d[v = g[u][j]] && d1 < p[v])
                q.push({v, d[v] = d1});
        }
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int k=0; k<t; ++k) {
        if (k) cout << endl;
        cout << solve() << endl;
    }
    return 0;
}