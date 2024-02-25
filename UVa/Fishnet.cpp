/**
 * UVa1301/LA2402
 * 渔网
 * Hakodate 2001
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 32
double a[N], b[N], c[N], d[N]; int n;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
} p[2][N], w[N];
typedef Point Vector;

Vector operator+ (const Vector& A, const Vector& B) {
    return Vector(A.x + B.x, A.y + B.y);
}

Vector operator- (const Vector& A, const Vector& B) {
    return Vector(A.x - B.x, A.y - B.y);
}

Vector operator* (const Vector& A, double p) {
    return Vector(A.x * p, A.y * p);
}

double Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

Point GetLineIntersection(const Point& P, const Vector& v, const Point& Q, const Vector& w) {
    Vector u = P - Q;
    return P + v * (Cross(w, u) / Cross(v, w));
}

void solve() {
    ++n; p[0][n].x = p[1][n].x = b[n] = 1.; p[0][0].y = p[0][n].y = 0.;
    for (int i=1; i<n; ++i) cin >> a[i], p[0][i].x = a[i];
    for (int i=1; i<n; ++i) cin >> b[i], w[i].x = b[i]-a[i];
    for (int i=1; i<n; ++i) cin >> c[i], w[i].y = 1.;
    for (int i=1; i<n; ++i) cin >> d[i], p[0][i].y = 0.;
    double s = 0.;
    for (int i=1; i<n; ++i) {
        Point (&t)[N] = p[i&1], (&r)[N] = p[~i&1]; Vector u, v(1, d[i]-c[i]);
        t[0].y = c[i]; t[n].y = d[i];
        for (int j=1; j<n; ++j) t[j] = GetLineIntersection(t[0], v, r[j], w[j]);
        for (int j=1; j<=n; ++j) s = max(s, Cross(u = t[j] - r[j-1], t[j-1]-t[j]) + Cross(u, t[j]-r[j]));
    }
    Point (&t)[N] = p[n&1], (&r)[N] = p[~n&1];
    for (int i = t[0].y = 1; i<=n; ++i) {
        t[i].x = b[i]; t[i].y = 1.; Vector u;
        s = max(s, Cross(u = t[i] - r[i-1], t[i-1]-t[i]) + Cross(u, t[i]-r[i]));
    }
    cout << s/2 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    while (cin >> n && n) solve();
    return 0;
}
