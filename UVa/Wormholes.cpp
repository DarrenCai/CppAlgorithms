/**
 * UVa12227/LA4618
 * 虫洞
 * NWERC 2009
 */

#include <iostream>
#include <queue>
using namespace std;

#define N 110
int s[N][N], f[N], g[N], t[N], d[N], x[N], y[N], z[N], m, n; bool inq[N], cyc[N];

int ceil_sqrt(int x) {
    int l = 0, r = min((x+1)>>1, 34642);
    while (l <= r) {
        int m = (l+r+1)>>1, y = m*m;
        if (y == x) return m;
        y < x ? l = m+1 : r = m-1;
    }
    return l;
}

bool update(int i) {
    queue<int> q;
    for (int j=2; j<n; j+=2) {
        g[j] = (cyc[j] ? t[j] : max(t[i]+d[i]+s[i+1][j], t[j])) + d[j];
        if (g[j] + s[j+1][i] < t[i]) {
            f[i] = min(f[i], t[i]); f[i+1] = min(f[i+1], min(f[i]+s[i][i+1], t[i]+d[i]));
            return cyc[i] = true;
        }
        q.push(j); inq[j] = true;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop(); inq[u] = false;
        for (int j=2; j<n; j+=2) if (!cyc[j]) {
            int v = max(g[u]+s[u+1][j], t[j]) + d[j];
            if (v < g[j]) {
                if (v + s[j+1][i] < t[i]) {
                    f[i] = min(f[i], t[i]); f[i+1] = min(f[i+1], min(f[i]+s[i][i+1], t[i]+d[i]));
                    return cyc[i] = true;
                }
                g[j] = v;
                if (!inq[j]) q.push(j), inq[j] = true;
            }
        }
    }
    return false;
}

void solve() {
    cin >> x[0] >> y[0] >> z[0] >> x[1] >> y[1] >> z[1] >> m; n = 2;
    for (int i=0; i<m; ++i) cin >> x[n] >> y[n] >> z[n++] >> x[n] >> y[n] >> z[n++] >> t[n-2] >> d[n-2];
    for (int i=0; i<n; ++i) for (int j=i; j<n; ++j) 
        s[i][j] = s[j][i] = ceil_sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])+(z[i]-z[j])*(z[i]-z[j]));
    for (int i=0; i<n; ++i) f[i] = s[i][0], cyc[i] = false;
    for (int i=2; i<n; i+=2) if (s[i][i+1] + d[i] < 0)
        f[i] = min(f[i], t[i]), f[i+1] = min(f[i+1], min(f[i]+s[i][i+1], t[i]+d[i])), cyc[i] = true;
    while (true) {
        bool updated = false;
        for (int i=0; i<n; i+=2) if (!cyc[i] && update(i)) updated = true;
        if (!updated) break;
    }
    queue<int> q;
    for (int i=2; i<n; ++i) q.push(i), inq[i] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop(); inq[u] = false;
        for (int i=0, v; i<n; ++i) if ((v = s[i][u] + f[u]) < f[i]) {
            f[i] = v;
            if (!inq[i]) q.push(i), inq[i] = true;
        }
        if (u&1) continue;
        int w = u+1, v = max(f[u], t[u]) + d[u];
        if (v < f[w]) {
            f[w] = v;
            if (!inq[w]) q.push(w), inq[w] = true;
        }
    }
    for (int i=2; i<n; ++i) f[1] = min(f[1], f[i] + s[1][i]);
    cout << f[1] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}