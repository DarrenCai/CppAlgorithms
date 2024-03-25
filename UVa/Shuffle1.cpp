/**
 * UVa11826
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define M 30
#define N 76
double d[N][N-1][M+1][M+1][M+1], e[N], f[N]; int n;

void solve() {
    int n, p1, q1, p2, q2; cin >> n >> p1 >> q1 >> p2 >> q2;
    if (q1==0 && q2==0) {
        cout << "IMPOSSIBLE" << endl; return;
    }
    if (p1>=n || p2>=n) {
        cout << 1. << endl; return;
    }
    f[n] = 0.; for (int i=0; i<n; ++i) f[i] = 1.;
    for (int i=n-1; i>=0; --i) {
        int a = min(n-i, q1), b = min(n-i, q1+q2);
        for (int j=0; j<=b; ++j) e[j] = 0.;
        for (int j=0; j<=a; ++j) {
            double &r = d[n][i][p1][q1][j];
            if (j+i == n) e[j] += r;
            else for (int k=0, s=i+j, m=min(n-s,q2); k<=m; ++k) e[j+k] += r*d[n][s][p2][q2][k];
        }
        for (int j=1; j<=b; ++j) f[i] += e[j]*f[i+j];
        f[i] /= 1. - e[0];
    }
    cout << f[0] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(6);
    for (int i=1; i<N; ++i) for (int j=0; j<i; ++j) {
        d[i][j][0][0][0] = 1.; for (int k=1; k<=M; ++k) d[i][j][0][0][k] = 0.;
        for (int k=0; k<M; ++k) {
            for (int s=0; s<=k; ++s) for (int p=0; p<=M; ++p) d[i][j][s][k+1][p] = 0.;
            if (k+1 <= j) d[i][j][k+1][k+1][0] = d[i][j][k][k][0] * 2*(j-k) / (i+j-2*k);
            if (k+1 >= i) d[i][j][k+1][k+1][i-j] = 1.;
            else for (int p=max(k-j, 0), q=min(i-j,k+1); p<q; ++p) {
                double &r = d[i][j][k+1][k+1][p+1] = d[i][j][k][k][p] * (i-j-p) / (i+j+p-2*k);
                if (p+1 <= i-j && k-p-1 < j) r += d[i][j][k][k][p+1] * 2*(j+p+1-k) / (i+j+p+1-2*k);
            }
        }
        for (int k=1; k<=M; ++k) for (int s=k-1; s>=0; --s) for (int p=0, q=min(i-j, k); p<=q; ++p)
            d[i][j][s][k][p] = (d[i][j][s][s][p] + d[i][j][s+1][k][p]*(k-s))/(k-s+1);
    }
    int t; cin >> t;
    for (int i=1; i<=t; ++i) cout << "Case " << i << ": ", solve();
    return 0;
}