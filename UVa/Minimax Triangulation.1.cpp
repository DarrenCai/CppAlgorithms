/**
 * UVa1331/LA3132
 * 最优三角剖分
 * NWERC 2004
 */

#include <iostream>
using namespace std;

#define INF 1000000000
#define M 52
int s[M][M][M], d[M][M], x[M], y[M], n;

int cross(int x1, int y1, int x2, int y2) {
    return x1*y2 - x2*y1;
}

int area(int i, int j, int k) {
    for (int t=0; t<n; ++t) {
        if (t!=i && t!=j && t!=k) {
            int x1 = x[i] - x[t], y1 = y[i] - y[t];
            int x2 = x[j] - x[t], y2 = y[j] - y[t];
            int x3 = x[k] - x[t], y3 = y[k] - y[t];
            int c1 = cross(x1, y1, x2, y2), c2 = cross(x2, y2, x3, y3), c3 = cross(x3, y3, x1, y1);
            if ((c1>0 && c2>0 && c3>0) || (c1<0 && c2<0 && c3<0)) return INF;
        }
    }
    return abs(y[i]*(x[k]-x[j]) + y[j]*(x[i]-x[k]) + y[k]*(x[j]-x[i]));
}

void solve() {
    cin >> n;
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i];
    for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j) for (int k=j+1; k<n; ++k) s[i][j][k] = area(i, j, k);
    for (int i=n-3; i>=0; --i) d[i][2] = s[i][i+1][i+2];
    for (int l=3; l<n; ++l) for (int i=n-l-1; i>=0; --i) {
        d[i][l] = min(max(s[i][i+1][i+l], d[i+1][l-1]), max(s[i][i+l-1][i+l], d[i][l-1]));
        for (int j=l-2; j>1; --j) d[i][l] = min(d[i][l], max(s[i][i+j][i+l], max(d[i][j], d[i+j][l-j])));
    }
    int ans = d[0][n-1];
    cout << (ans>>1) << '.' << (ans&1 ? 5 : 0) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}