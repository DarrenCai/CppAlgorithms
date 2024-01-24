/**
 * UVa1340/LA3218
 * 找边界
 * NEERC 2004
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define eps 1e-10
struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    void Normalize() {
        double l = sqrt(x*x + y*y); x /= l; y /= l;
    }
};
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

bool operator< (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator!= (const Point& a, const Point& b) {
    return a.x != b.x || a.y != b.y;
}

double Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

double Dot(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0. ? -1 : 1);
}

bool SegmentProperIntersect(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

double LineInterp(const Point& P, const Vector& v, const Point& Q, const Vector& w) {
    Vector u = P - Q;
    return Cross(w, u) / Cross(v, w);
}

#define N 102
Point p[N], q[N*N]; int c[N], m, n, s, x, d;

void solve() {
    for (int i=s=0; i<n; ++i) {
        cin >> p[i].x >> p[i].y;
        if (p[i] < p[s]) s = i;
    }
    Vector v = p[s+1<n ? s+1 : 0] - p[s], w = p[s ? s-1 : n-1] - p[s]; v.Normalize(); w.Normalize();
    d = v.y > w.y ? -1 : 1; x = d>0 ? (s+1<n ? s+1 : 0) : (s ? s-1 : n-1); q[m = 0] = p[s];
    while (m < 1 || q[m] != q[0]) {
        v = p[x] - q[m]; double t = 1.; int y = 0;
        for (int i=0, j; i<n; ++i) if (SegmentProperIntersect(p[x], q[m], p[i], p[j = i+1<n ? i+1 : 0])) {
            double z = LineInterp(q[m], v, p[i], p[j]-p[i]), w = dcmp(z-t);
            if (w < 0) c[0] = i, y = 1, t = z;
            else if (w == 0) c[y++] = i;
        }
        if (t < 1.) {
            q[m+1] = q[m] + v*t; ++m; v.Normalize();
            double a = 1.;
            while (y--) {
                int i = c[y], j = i+1<n ? i+1 : 0;
                w = p[j] - p[i]; w.Normalize();
                if (Cross(v, w) < 0.) {
                    double b = Dot(v, w);
                    if (b < a) a = b, x = j, d = 1;
                } else {
                    w.x = -w.x; w.y = -w.y;
                    double b = Dot(v, w);
                    if (b < a) a = b, x = i, d = -1;
                }
            }
        } else q[++m] = p[x], x = d>0 ? (x+1<n ? x+1 : 0) : (x ? x-1 : n-1);
    }
    cout << m << endl;
    for (int i=0; i<m; ++i) cout << q[i].x << ' ' << q[i].y << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(4);
    while (cin >> n) solve();
    return 0;
}