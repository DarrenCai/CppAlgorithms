/**
 * UVa1304/LA2512
 * 艺术画廊
 * SEERC 2002
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

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

double Area2(const Point* p, int n) {
    double area2 = p[0].y * (p[n-1].x - p[1].x) + p[n-1].y * (p[n-2].x - p[0].x);
    for (int i=n-2; i>0; --i) area2 += p[i].y * (p[i-1].x - p[i+1].x);
    return area2;
}

struct Line {
    Point P;
    Vector v;
    double ang;
    Line() {}
    Line(const Point& P, const Vector& v):P(P),v(v){ ang = atan2(v.y, v.x); }
    bool operator< (const Line& L) const {
        return ang < L.ang;
    }
};

bool OnLeft(const Line& L, const Point& p) {
    return Cross(L.v, p-L.P) > 0;
}

Point GetIntersection(const Line& a, const Line& b) {
    Vector u = a.P-b.P;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.P + a.v*t;
}

#define N 1510
Point p[N], r[N]; Line L[N], q[N]; int n;

double solve() {
    cin >> n;
    for (int i=0; i<n; ++i) cin >> p[i].x >> p[i].y;
    bool f = Area2(p, n) > 0.;
    for (int i=0; i<n; ++i) {
        int j= i+1<n ? i+1 : 0;
        L[i] = Line(f ? p[i] : p[j], f ? p[j] - p[i] : p[i] - p[j]);
    }
    sort(L, L+n);
    int first, last;
    q[first = last = 0] = L[0];
    for (int i=1; i<n; ++i) {
        while (first < last && !OnLeft(L[i], r[last-1])) --last;
        while (first < last && !OnLeft(L[i], r[first])) ++first;
        q[++last] = L[i];
        if (Cross(q[last].v, q[last-1].v) == 0.) {
            --last;
            if (OnLeft(q[last], L[i].P)) q[last] = L[i];
        }
        if (first < last) r[last-1] = GetIntersection(q[last-1], q[last]);
    }
    while (first < last && !OnLeft(q[first], r[last-1])) --last;
    if (last - first <= 1) return 0.;
    r[last] = GetIntersection(q[last], q[first]);
    return Area2(r+first, last-first+1) / 2.;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(2);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}