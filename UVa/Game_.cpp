/**
 * UVa1413/LA4049
 * 传球游戏
 * NEERC 2007
 * 好不容易把马尔可夫递推想清楚了，结果还要避免精度丢失(*´∇｀*)
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 50
double p[N], f[N][N][2][2], g[N][N][2]; int n, k;

double solve(int n, int k) {
    for (int i=1; i<n; ++i) {
        cin >> p[i];
        f[i][i][0][1] = f[i][i][1][1] = p[i];
        f[i][i][0][0] = f[i][i][1][0] = 1-p[i];
    }
    for (int l=1; l<n; ++l) for (int i=1, j; (j = i+l) < n; ++i) {
        /* 理论上f[i][j][0][0] + f[i][j][0][1] = 1，求一个即可
         * 但这样其中一个因为精度问题变成0/1时，另外一个伴随着也出现精度问题，
         * 它两分开求能消除精度问题相互干扰的情况
         */
        f[i][j][0][0] = (1-p[i]) / ((1-p[i]) + p[i]*f[i+1][j][0][1]);
        f[i][j][0][1] = p[i]*f[i+1][j][0][1] / ((1-p[i]) + p[i]*f[i+1][j][0][1]);
        f[i][j][1][1] = p[j] / (p[j] + (1-p[j])*f[i][j-1][1][0]);
        f[i][j][1][0] = (1-p[j])*f[i][j-1][1][0] / (p[j] + (1-p[j])*f[i][j-1][1][0]);
    }
    for (int i=1; i<n; ++i) for (int j=i; j<n; ++j) g[i][j][0] = g[i][j][1] = 0;
    g[k][k][0] = 1-p[k]; g[k][k][1] = p[k];
    for (int l=1; l<n; ++l) for (int i=1, j; i<=k && (j = i+l) < n; ++i) if (j >= k) {
        g[i][j][1] = g[i][j-1][1]*f[i][j][1][1] + g[i+1][j][0]*f[i][j][0][1];
        g[i][j][0] = g[i+1][j][0]*f[i][j][0][0] + g[i][j-1][1]*f[i][j][1][0];
    }
    return g[1][n-1][0] + g[1][n-1][1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(10);
    while (cin>>n>>k) cout << solve(n, k) << endl;
    return 0;
}