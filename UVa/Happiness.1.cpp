/**
 * UVa10498
 * 食物分配
 */

#include <iostream>
#include <cmath>
using namespace std;

#define INF 1e9
#define eps 1e-10
#define M 22
#define N 22
double a[M][N]; int B[M], C[N], m, n;

void pivot(int r, int c) {
    int t = C[c]; C[c] = B[r]; B[r] = t;
    a[r][c] = 1 / a[r][c];
    for (int j = 0; j <= n; j++) if (j != c) a[r][j] *= a[r][c];
    for (int i = 0; i <= m; i++) if (i != r) {
        for (int j = 0; j <= n; j++) if (j != c) a[i][j] -= a[i][c] * a[r][j];
        a[i][c] = -a[i][c] * a[r][c];
    }
}

bool feasible() {
    while (true) {
        int r, c; double p = INF;
        for (int i = 0; i < m; i++) if (a[i][n] < p) p = a[r = i][n];
        if (p > -eps) return true;
        p = 0.;
        for (int i = 0; i < n; i++) if (a[r][i] < p) p = a[r][c = i];
        if (p > -eps) return false;
        p = a[r][n] / a[r][c];
        for (int i = r+1; i < m; i++) if (a[i][c] > eps) {
            double v = a[i][n] / a[i][c];
            if (v < p) r = i, p = v;
        }
        pivot(r, c);
    }
}

int simplex(double& ret) {
    for (int i = 0; i < n; i++) C[i] = i;
    for (int i = 0; i < m; i++) B[i] = n+i;
    if (!feasible()) return 0;
    while (true) {
        int r, c; double p = 0.;
        for (int i = 0; i < n; i++) if (a[m][i] > p) p = a[m][c = i];
        if (p < eps) {
            ret = -a[m][n];
            return 1;
        }
        p = INF;
        for (int i = 0; i < m; i++) if (a[i][c] > eps) {
            double v = a[i][n] / a[i][c];
            if (v < p) r = i, p = v;
        }
        if (p == INF) return -1;
        pivot(r, c);
    }
}

double solve() {
    double ans = a[m][n] = 0.;
    for (int i=0; i<n; ++i) cin >> a[m][i];
    for (int i=0; i<m; ++i) {
        for (int j=0; j<n; ++j) cin >> a[i][j];
        cin >> a[i][n];
    }
    simplex(ans);
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) cout << "Nasa can spend " << int(ceil(m*solve())) << " taka." << endl;
    return 0;
}