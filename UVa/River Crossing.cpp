/**
 * UVa10514
 * 过河
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define R 101
#define N 14
#define M 21

int x[R], y[R], x2[R], y2[R], px[N][M], py[N][M], m[N], r1, r2, n; double d[N][N];

double dis(int xa, int ya, int xb, int yb) {
    return sqrt((xa-xb)*(xa-xb) + (ya-yb)*(ya-yb));
}

double dis(int xa, int ya, int xb, int yb, int xc, int yc, int xd, int yd) {
    double d = min(min(dis(xa, ya, xc, yc), dis(xa, ya, xd, yd)), min(dis(xb, yb, xc, yc), dis(xb, yb, xd, yd)));
    int dx = xb-xa, dy = yb-ya, vx = xc-xa, vy = yc-ya; double s = sqrt(dx*dx + dy*dy), t = (dx*vx + dy*vy) / s;
    if (t >= 0. && t <= s) d = min(d, sqrt(vx*vx + vy*vy - t*t));
    vx = xd-xa; vy = yd-ya; t = (dx*vx + dy*vy) / s;
    if (t >= 0. && t <= s) d = min(d, sqrt(vx*vx + vy*vy - t*t));
    dx = xd-xc; dy = yd-yc; vx = xa-xc; vy = ya-yc; s = sqrt(dx*dx + dy*dy); t = (dx*vx + dy*vy) / s;
    if (t >= 0. && t <= s) d = min(d, sqrt(vx*vx + vy*vy - t*t));
    vx = xb-xc; vy = yb-yc; t = (dx*vx + dy*vy) / s;
    if (t >= 0. && t <= s) d = min(d, sqrt(vx*vx + vy*vy - t*t));
    return d;
}

double dis(int xa, int ya, int xb, int yb, int i) {
    double d = dis(xa, ya, px[i][0], py[i][0]);
    for (int j=0; j<m[i]; ++j) d = min(d, dis(xa, ya, xb, yb, px[i][j], py[i][j], px[i][j+1], py[i][j+1]));
    return d;
}

double dis(int i, int j) {
    double d = dis(px[i][0], py[i][0], px[j][0], py[j][0]);
    for (int a=0; a<m[i]; ++a) d = min(d, dis(px[i][a], py[i][a], px[i][a+1], py[i][a+1], j));
    return d;
}

void solve() {
    cin >> r1 >> r2 >> n; ++n;
    for (int i=0; i<r1; ++i) cin >> x[i] >> y[i];
    for (int i=0; i<r2; ++i) cin >> x2[i] >> y2[i];
    for (int i=1; i<n; ++i) {
        cin >> m[i];
        for (int j=0; j<m[i]; ++j) cin >> px[i][j] >> py[i][j];
        px[i][m[i]] = px[i][0]; py[i][m[i]] = py[i][0];
        d[0][i] = dis(x[0], y[0], px[i][0], py[i][0]); d[i][n] = dis(x2[0], y2[0], px[i][0], py[i][0]);
    }
    d[0][n] = dis(x[0], y[0], x2[0], y2[0]);
    for (int i=1; i<r1; ++i) for (int j=1; j<r2; ++j)
        d[0][n] = min(d[0][n], dis(x[i-1], y[i-1], x[i], y[i], x2[j-1], y2[j-1], x2[j], y2[j]));
    for (int i=1; i<n; ++i) {
        for (int j=1; j<r1; ++j) d[0][i] = min(d[0][i], dis(x[j-1], y[j-1], x[j], y[j], i));
        for (int j=1; j<r2; ++j) d[i][n] = min(d[i][n], dis(x2[j-1], y2[j-1], x2[j], y2[j], i));
        for (int j=i+1; j<n; ++j) d[i][j] = d[j][i] = dis(i, j);
    }
    for (int k=1; k<n; ++k) for (int i=0; i<n; ++i) if (i != k) for (int j=1; j<=n; ++j) if (j != k)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    cout << d[0][n] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}