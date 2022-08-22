/**
 * UVa1424/LA4256
 * 商人
 * Asia Seoul 2008
 */

#include <iostream>
using namespace std;

#define N 110
bool c[N][N]; int d[N<<1][N];

int solve() {
    int n1, n2, n, x; cin >> n1 >> n2;
    for (int i=1; i<=n1; ++i) for (int j=1; j<=n1; ++j) c[i][j] = i==j;
    for (int i=0; i<n2; ++i) {
        int u, v; cin >> u >> v;
        c[u][v] = c[v][u] = true;
    }
    cin >> n >> x;
    for (int i=1; i<=n1; ++i) d[1][i] = x!=i;
    for (int i=2; i<=n; ++i) {
        cin >> x;
        for (int j=1; j<=n1; ++j) {
            d[i][j] = N<<1;
            for (int k=1; k<=n1; ++k) if (c[j][k]) d[i][j] = min(d[i][j], (j!=x) + d[i-1][k]);
        }
    }
    int ans = N<<1;
    for (int i=1; i<=n1; ++i) ans = min(ans, d[n][i]);
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}