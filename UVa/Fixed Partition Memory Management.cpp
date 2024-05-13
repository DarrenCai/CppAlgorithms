/**
 * UVa1006/LA2238
 * 固定分区内存管理
 * World Finals 2001
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define INF 1000000000
#define M 11
#define N 51
int x[N][3], mem[M], a[M], c[M], w[N][M][N], slack[M][N], lx[N], ly[M][N], p[M][N], m, n, kase = 0; bool s[N], t[M][N];

bool match(int i) {
    s[i] = true;
    for (int j=1; j<=m; ++j) for (int k=1; k<=n; ++k) if (!t[j][k]) {
        int d = lx[i] + ly[j][k] - w[i][j][k];
        if (d == 0) {
            t[j][k] = true;
            if (!p[j][k] || match(p[j][k])) {
                p[j][k] = i;
                return true;
            }
        } else slack[j][k] = min(slack[j][k], d);
    }
    return false;
}

void km() {
    for (int i=1; i<=n; ++i) lx[i] = -INF;
    for (int i=1; i<=m; ++i) for (int j=1; j<=n; ++j) p[i][j] = ly[i][j] = 0;
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) for (int k=1; k<=n; ++k) lx[i] = max(lx[i], w[i][j][k]);
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) for (int k=1; k<=n; ++k) slack[j][k] = INF;
        while (true) {
            for (int j=1; j<=n; ++j) s[j] = false;
            for (int j=1; j<=m; ++j) for (int k=1; k<=n; ++k) t[j][k] = false;
            if (match(i)) break;
            int a = INF;
            for (int j=1; j<=m; ++j) for (int k=1; k<=n; ++k) if (!t[j][k]) a = min(a, slack[j][k]);
            for (int j=1; j<=n; ++j) if (s[j]) lx[j] -= a;
            for (int j=1; j<=m; ++j) for (int k=1; k<=n; ++k) t[j][k] ? ly[j][k] += a : slack[j][k] -= a;
        }
    }
}

void solve() {
    for (int i=1; i<=m; ++i) cin >> mem[i];
    for (int i=1; i<=n; ++i) {
        int k; cin >> k;
        for (int j=k; j>0; --j) cin >> a[j] >> c[j];
        for (int j=1, p; j<=m; ++j) {
            for (p=1; p<=k; ++p) if (mem[j] >= a[p]) {
                for (int k=1; k<=n; ++k) w[i][j][k] = -c[p]*k;
                break;
            }
            if (p > k) for (int k=1; k<=n; ++k) w[i][j][k] = -INF;
        }
    }
    km();
    int s = 0;
    for (int i=1; i<=n; ++i) s -= lx[i];
    for (int i=1; i<=m; ++i) for (int j=1; j<=n; ++j) s -= ly[i][j];
    for (int i=1, j; i<=m; ++i) if (p[i][1]) {
        for (int k=1; k<=n; ++k) if (p[i][k]) j = k;
        for (int k=j, t=0, y; k>0; --k) x[y = p[i][k]][0] = i, x[y][1] = t, x[y][2] = (t -= w[y][i][k]/k);
    }
    cout << "Case " << ++kase << endl << "Average turnaround time = " << s/double(n) << endl;
    for (int i=1; i<=n; ++i)
        cout << "Program " << i << " runs in region " << x[i][0] << " from " << x[i][1] << " to " << x[i][2] << endl;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    while (cin >> m >> n && m) solve();
    return 0;
}