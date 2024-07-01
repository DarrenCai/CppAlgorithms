/**
 * UVa1516/LA5906
 * NWERC 2011
 */

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define N 102
int f[N], s[N], m, n; double w[N][N]; char names[N][22], t[22]; long long x[N], y[N];

int idx() {
    cin >> t;
    for (int i=0; i<n; ++i) if (!strcmp(names[i], t)) return i;
    return n;
}

int dp(int u) {
    if (f[u] > 0) return f[u];
    f[u] = 1; s[u] = -1;
    for (int v=0; v<n; ++v) if (w[u][v] <= 0. && 1 + dp(v) > f[u]) f[u] = 1 + f[v], s[u] = v;
    return f[u];
}

void solve() {
    cin >> n >> m;
    for (int i=0; i<n; ++i) cin >> names[i] >> x[i] >> y[i], f[i] = 0;
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) w[i][j] = 1e9;
    while (m--) {
        int u = idx(), v, z; cin >> t; v = idx(); cin >> t >> t; z = idx(); f[v] = f[z] = 1;
        w[v][z] = min(w[v][z], sqrt((x[z]-x[u])*(x[z]-x[u]) + (y[z]-y[u])*(y[z]-y[u])) - 
                                sqrt((x[v]-x[u])*(x[v]-x[u]) + (y[v]-y[u])*(y[v]-y[u])));
    }
    for (int k=0; k<n; ++k) for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) {
        w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
        if (w[i][j] + w[j][i] <= 0.) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
    }
    for (int i=m=0; i<n; ++i) if (f[i]) ++m, f[i] = 0;
    for (int i=0; i<n; ++i) if (dp(i) == m) {
        cout << names[i];
        while (s[i] >= 0) cout << ' ' << names[i = s[i]];
        cout << endl;
        return;
    }
    cout << "UNKNOWN" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}