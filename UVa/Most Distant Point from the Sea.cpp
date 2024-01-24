/**
 * UVa1396/LA3890
 * 离海最远的点
 * Tokyo 2007
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define eps 1e-8
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

double Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

struct Line { Point P; Vector v; };

bool OnLeft(const Line& L, const Point& p) {
    return Cross(L.v, p-L.P) > 0;
}

Point GetIntersection(const Line& a, const Line& b) {
    Vector u = a.P-b.P;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.P + a.v*t;
}

#define N 102
Point v[N], p[N]; Line L[N], q[N]; int n;

bool HalfplaneIntersect() {
    int first = 0, last = 0; q[0] = L[0];
    for (int i=1; i<n; ++i) {
        while (first < last && !OnLeft(L[i], p[last-1])) --last;
        while (first < last && !OnLeft(L[i], p[first])) ++first;
        q[++last] = L[i];
        if (abs(Cross(q[last].v, q[last-1].v)) < eps) {
            --last;
            if (OnLeft(q[last], L[i].P)) q[last] = L[i];
        }
        if (first < last) p[last-1] = GetIntersection(q[last-1], q[last]);
    }
    while (first < last && !OnLeft(q[first], p[last-1])) --last;
    return last - first > 1;
}

void solve() {
    for (int i=0; i<n; ++i) cin >> v[i].x >> v[i].y;
    for (int i=0; i<n; ++i) L[i].v = v[i+1<n ? i+1 : 0] - v[i], L[i].v.Normalize();
    double l = 0., r = 5000.;
    while (r-l > eps) {
        double m = (l+r) / 2;
        for (int i=0; i<n; ++i) L[i].P.x = v[i].x - m*L[i].v.y, L[i].P.y = v[i].y + m*L[i].v.x;
        HalfplaneIntersect() ? l = m + eps : r = m;
    }
    cout << r << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(6);
    while (cin >> n && n) solve();
    return 0;
}