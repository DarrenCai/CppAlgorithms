/**
 * UVa11177
 * 多边形怪兽
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define eps 1e-4
#define N 52
struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    void Normalize() {
        double l = sqrt(x*x + y*y); x /= l; y /= l;
    }
} p[N], o;
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

double Dot(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

double Length(const Vector& A) {
    return sqrt(Dot(A, A));
}

double Angle(const Vector& A, const Vector& B) {
    return acos(Dot(A, B) / Length(A) / Length(B));
}

double Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

double DistanceToSegment(const Point& P, const Point& A, const Point& B) {
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if (Dot(v1, v2) < 0) return Length(v2);
    if (Dot(v1, v3) > 0) return Length(v3);
    return abs(Cross(v1, v2)) / Length(v1);
}

double R; int n, kase = 0;

bool check(double r) {
    double s = 0, t = r*r;
    for (int i=1; i<n; ++i) {
        if (DistanceToSegment(o, p[i-1], p[i]) < r) {
            double a = Length(p[i-1]), b = Length(p[i]);
            if (a > r) {
                Vector v = p[i] - p[i-1]; v.Normalize(); double c = Dot(v, o-p[i-1]), d = sqrt(c*c + t - a*a);
                if (c+d < 0. || c-d >= Length(p[i] - p[i-1])) {
                    s += Angle(p[i-1], p[i]) * t; continue;
                }
                Point q = p[i-1] + v * (c - d);
                if (b > r) {
                    Point r = p[i-1] + v * (c + d);
                    s += (Angle(q, p[i-1]) + Angle(r, p[i])) * t + abs(Cross(q, r));
                } else s += Angle(q, p[i-1]) * t + abs(Cross(q, p[i]));
            } else if (b > r) {
                Vector v = p[i-1] - p[i]; v.Normalize(); double c = Dot(v, o-p[i]);
                Point q = p[i] + v * (c - sqrt(c*c + t - b*b));
                s += Angle(q, p[i]) * t + abs(Cross(q, p[i-1]));
            } else s += abs(Cross(p[i-1], p[i]));
        } else s += Angle(p[i-1], p[i]) * t;
    }
    return s >= R;
}

void solve() {
    double l = eps, r = 0.; cin >> R; R *= 2;
    for (int i=0; i<n; ++i) cin >> p[i].x >> p[i].y, r = max(r, p[i].x*p[i].x + p[i].y*p[i].y);
    p[n++] = p[0]; r = sqrt(r);
    while (l + eps < r) {
        double m = (l+r)/2;
        check(m) ? r = m : l = m+eps;
    }
    cout << "Case " << ++kase << ": " << r << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    while (cin >> n && n) solve();
    return 0;
}
