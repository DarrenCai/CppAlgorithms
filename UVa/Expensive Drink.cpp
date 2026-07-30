/**
 * UVa1410/LA4027
 * 昂贵的饮品
 * Beijing 2007
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define INF 1e200
#define eps 1e-8
#define M 205
#define N 4
double a[M][N]; int B[M], C[N], m, n, L, R, kase = 0;

void pivot(int r, int c) {
    double t = a[r][c]; int e = C[c]; C[c] = B[r]; B[r] = e; a[r][c] = 1.;
    for (int i = 0; i <= n; ++i) a[r][i] /= t;
    for (int i = 0; i <= m; ++i) if (i != r && abs(a[i][c]) > eps){
        t = a[i][c]; a[i][c] = 0;
        for (int j = 0; j <= n; j++) a[i][j] -= a[r][j] * t;
    }
}

bool feasible() {
    while (true) {
        int r = -1, c = -1;
        for (int i = 0; i < m; i++) if (a[i][n] < -eps && (r < 0 || (rand() & 1))) r = i;
        if (r < 0) break;
        for (int i = 0; i < n; i++) if (a[r][i] < -eps && (c < 0 || (rand() & 1))) c = i;
        if (c < 0) return false;
        pivot(r, c);
    }
    return true;
}

int simplex() {
    for (int i = 0; i < n; i++) C[i] = i;
    for (int i = 0; i < m; i++) B[i] = n+i;
    if (!feasible()) return 0;
    while (true) {
        int r = -1, c = -1; double p = INF;
        for (int i = 0; i < n; i++) if (a[m][i] > eps) {
            c = i; break;
        }
        if (c < 0) break;
        for (int i = 0; i < m; i++) if (a[i][c] > eps) {
            double v = a[i][n] / a[i][c];
            if (v < p) r = i, p = v;
        }
        if (r < 0) return -1;
        pivot(r, c);
    }
    return 1;
}

void solve() {
    cin >> L >> R; m = n+1 << 1;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<3; ++j) cin >> a[i][j], a[i+n][j] = -a[i][j];
        int p; cin >> p;
        a[i][3] = p - L; a[i+n][3] = R - p;
    }
    a[m-2][0] = 1.; a[m-2][1] = -1.; a[m-2][2] = a[m-2][3] = 0.;
    a[m-1][0] = a[m-1][3] = 0.; a[m-1][1] = 1.; a[m-1][2] = -1.;
    a[m][n = 3] = -R;
    for (int i=0; i<3; ++i) cin >> a[m][i];
    int r = simplex();
    cout << "Case " << ++ kase << ": ";
    if (r == 0) cout << "Inconsistent data" << endl;
    else if (r < 0) cout << "Too expensive!" << endl;
    else cout << -a[m][n] + eps << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(4);
    while (cin >> n && n) solve();
    return 0;
}
