/**
 * UVa1331
 * 最优三角剖分
 * 注意：这里可能是凹多边形，需要排除不合理的三角形（即包含了其它顶点的三角形）
 */

#include <iostream>
using namespace std;

#define max(a, b) (a>b ? a:b)
#define min(a, b) (a<b ? a:b)
#define INF 1e8
#define N 55
int x[N], y[N], d[N][N], n;

int cross(int x1, int y1, int x2, int y2) {
    return x1*y2 - x2*y1;
}

bool check(int i, int j, int k) {
    for (int t=0; t<n; ++t) {
        if (t!=i && t!=j && t!=k) {
            int x1 = x[i] - x[t], y1 = y[i] - y[t];
            int x2 = x[j] - x[t], y2 = y[j] - y[t];
            int x3 = x[k] - x[t], y3 = y[k] - y[t];
            int c1 = cross(x1, y1, x2, y2), c2 = cross(x2, y2, x3, y3), c3 = cross(x3, y3, x1, y1);
            if ((c1>0 && c2>0 && c3>0) || (c1<0 && c2<0 && c3<0)) return false;
        }
    }
    return true;
}

int calc(int i, int j, int k) {
    if (!check(i, j, k)) return INF;
    int s = x[i]*y[j] + y[i]*x[k] + x[j]*y[k] - y[j]*x[k] - y[k]*x[i] - y[i]*x[j];
    return s > 0 ? s : -s;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        cin >> n; for (int i=0; i<n; ++i) cin >> x[i] >> y[i];
        for (int l=2; l<n; ++l) for (int i=0, j; (j=i+l) < n; ++i)
            if (l == 2) {
                d[i][j] = calc(i, i+1, j);
            } else {
                d[i][j] = max(calc(i, i+1, j), d[i+1][j]);
                for (int k=i+2; k<j; ++k) d[i][j] = min(d[i][j], max(calc(i, k, j), max(d[i][k], d[k][j])));
            }
        cout << d[0][n-1]/2 << '.' << (d[0][n-1]&1 ? 5 : 0) << endl;
    }
    return 0;
}