/**
 * UVa1475/LA4992
 * 丛林警戒队
 * NEERC 2010
 */

#include <iostream>
#include <cmath>
using namespace std;

#define eps 1e-8
struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
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

#define N 50020
Point p[N]; Line L[N], q[N]; double x[N], y[N]; int n;

bool HalfplaneIntersect(int k) {
    for (int i=0; i<n; ++i) {
        int j = i+k < n ? i+k : i+k-n; double s = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
        L[i].P.x = x[j]; L[i].P.y = y[j]; L[i].v.x = (x[i]-x[j]) / s; L[i].v.y = (y[i]-y[j]) / s;
    }
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
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i];
    int l = 1, r = (n-1)>>1;
    while (l <= r) {
        int m = (l+r) >> 1;
        HalfplaneIntersect(m) ? l = m+1 : r = m-1;
    }
    cout << r << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n) solve();
    return 0;
}