/**
 * UVa10828
 * 随机程序
 * 注意：本题不适合用高斯消元法，应采用高斯-约当消元法
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 102
int g[N][N], c[N], n, kase = 0; double a[N][N], eps = 1e-8; bool inf[N];

// 高斯-约当消元, x[i] = a[i][n] / a[i][i]
void gauss_jordan() {
    for (int i=0; i<n; ++i) {
        int r = i;
        for (int j=i+1; j<n; ++j) if (abs(a[j][i]) > abs(a[r][i])) r = j;
        if (abs(a[r][i]) < eps) continue;
        if (r != i) for (int j=0; j<=n; ++j) {
            double t = a[i][j]; a[i][j] = a[r][j]; a[r][j] = t;
        }
        for (int j=0; j<n; ++j) if (j != i) {
            for (int k=n; k>=i; --k) a[j][k] -= a[j][i]/a[i][i] * a[i][k];
        }
    }
}

void solve() {
    for (int i=0; i<n; ++i) {
        inf[i] = c[i] = 0; a[i][n] = i == 0;
        for (int j=0; j<n; ++j) a[i][j] = j==i;
    }
    int u, v, q;
    while (cin>>u>>v && u--) g[u][c[u]++] = --v;
    for (int i=0; i<n; ++i) if (c[i]) {
        double f = 1. / c[i];
        for (int j=0; j<c[i]; ++j) a[g[i][j]][i] -= f;
    }
    gauss_jordan();
    for (int i=n-1; i>=0; --i) {
        if (abs(a[i][i])<eps && abs(a[i][n])>eps) inf[i] = true;
        if (inf[i]) continue;
        for (int j=i+1; j<n; ++j) if (abs(a[i][j])>eps && inf[j]) {
            inf[i] = true; break;
        }
    }
    cout << "Case #" << ++kase << ':' << endl;
    cin >> q;
    while (q--) {
        cin >> u; --u;
        inf[u] ? cout << "infinity" << endl : cout << (abs(a[u][u])<eps ? 0. : a[u][n] / a[u][u]) << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    while (cin>>n && n) solve();
    return 0;
}