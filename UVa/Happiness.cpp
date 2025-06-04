/**
 * UVa10498
 * 食物分配
 */

#include <iostream>
#include <cmath>
using namespace std;

#define INF 1e9
#define M 22
#define N 22
double a[M][N], b[M], c[N], ans; int m, n;

void pivot(int l, int e) {
    b[l] /= a[l][e];
    for (int j = 1; j <= n; j++) if (j != e) a[l][j] /= a[l][e];
    a[l][e] = 1 / a[l][e];

    for (int i = 1; i <= m; i++) if (i != l && abs(a[i][e]) > 0.) {
        b[i] -= a[i][e] * b[l];
        for (int j = 1; j <= n; j++) if (j != e) a[i][j] -= a[i][e] * a[l][j];
        a[i][e] = -a[i][e] * a[l][e];
    }

    ans += c[e] * b[l];
    for (int j = 1; j <= n; j++) if (j != e) c[j] -= c[e] * a[l][j]; c[e] = -c[e] * a[l][e];
}

double simplex() {
    while (true) {
        int e = 0, l = 0;
        for (e = 1; e <= n; e++) if (c[e] > 0.) break;
        if (e == n + 1) return ans;
        double mn = INF;
        for (int i = 1; i <= m; i++) {
            if (a[i][e] > 0. && mn > b[i] / a[i][e]) {
                mn = b[i] / a[i][e];
                l = i;
            }
        }
        if (mn == INF) return INF;
        pivot(l, e);
    }
}

double solve() {
    ans = 0.;
    for (int i=1; i<=n; ++i) cin >> c[i];
    for (int i=1; i<=m; ++i) {
        for (int j=1; j<=n; ++j) cin >> a[i][j];
        cin >> b[i];
    }
    return simplex();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) cout << "Nasa can spend " << int(ceil(m*solve())) << " taka." << endl;
    return 0;
}