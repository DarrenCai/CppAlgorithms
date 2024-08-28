/**
 * UVa821/LA5221
 * 网页跳跃
 * World Finals 2000
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 102
int d[N][N], a, b, kase = 0; bool vis[N];

void solve() {
    for (int i=1; i<N; ++i) for (int j=i; j<N; ++j) d[i][j] = d[j][i] = N;
    double s = 0.; int c = 0, n = 0;
    while (a) n = max(n, max(a, b)), d[a][b] = 1, cin >> a >> b;
    for (int k=1; k<=n; ++k) for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j)
        d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
    for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) if (i!=j && d[i][j]<N) s += d[i][j], ++c;
    cout << "Case " << ++kase << ": average length between pages = " << s/c << " clicks" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    while (cin >> a >> b && a) solve();
    return 0;
}