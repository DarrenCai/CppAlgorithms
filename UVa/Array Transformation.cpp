/**
 * UVa12003
 * 数组变换
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define M 300
#define N 1010
int a[M*N], b[M][N], n, m; long long u;

void solve() {
    cin >> n >> m >> u;
    for (int i=1; i<=n; ++i) cin >> a[i];
    for (int i=0, k=0, c = n/N; i<c; ++i) {
        for (int j=0; j<N; ++j) b[i][j] = a[++k];
        sort(b[i], b[i]+N);
    }
    while (m--) {
        int l, r, v, p; cin >> l >> r >> v >> p;
        int s = (l+N-1)/N, t = (r-1)/N, k = 0;
        if (s < t) {
            for (int i=s*N; i>=l; --i) if (a[i] < v) ++k;
            for (int i=t*N+1; i<=r; ++i) if (a[i] < v) ++k;
            for (int i=s; i<t; ++i) k += lower_bound(b[i], b[i]+N, v) - b[i];
        } else for (int i=l; i<=r; ++i) if (a[i] < v) ++k;
        if ((v = (p-1)/N) < n/N) {
            s = lower_bound(b[v], b[v]+N, a[p]) - b[v]; b[v][s] = a[p] = u*k/(r-l+1);
            while (s+1 < N && a[p] > b[v][s+1]) t = b[v][s+1], b[v][s+1] = a[p], b[v][s++] = t;
            while (s > 0 && a[p] < b[v][s-1]) t = b[v][s-1], b[v][s-1] = a[p], b[v][s--] = t;
        } else a[p] = u*k/(r-l+1);
    }
    for (int i=1; i<=n; ++i) cout << a[i] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}