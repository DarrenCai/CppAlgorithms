/**
 * UVa1298/LA2218
 * 铁人三项
 * NEERC 2000
 */

#include <iostream>
#include <cmath>
#include <algorithm>
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

struct Line {
    Point P; Vector v; double ang;
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

#define N 105
Point p[N]; Line L[N], q[N]; int u[N], v[N], w[N], m, n; double K = 10000.;

bool judge(int i) {
    for (int j=m=0; j<n; ++j) if (i != j) {
        if (u[i] <= u[j] && v[i] <= v[j] && w[i] <= w[j]) return false;
        if (u[i] >= u[j] && v[i] >= v[j] && w[i] >= w[j]) continue;
        double c = K/w[j] - K/w[i], a = K/u[j] - K/u[i] - c, b = K/v[j] - K/v[i] - c, s = sqrt(a*a + b*b);
        L[m].P.x = abs(a)>abs(b) ? -c/a : 0.; L[m].P.y = abs(a)>abs(b) ? 0. : -c/b;
        L[m].v.x = b/s; L[m].v.y = -a/s; L[m++].ang = atan2(-a, b);
    }
    L[m].P.x = 0.; L[m].P.y = 0.; L[m].ang = -M_PI_2; L[m].v.x = 0.; L[m++].v.y = -1.;
    L[m].P.x = 0.; L[m].P.y = 0.; L[m].ang = 0.; L[m].v.x = 1.; L[m++].v.y = 0;
    L[m].P.x = 0.; L[m].P.y = 1.; L[m].ang = 3*M_PI_4; L[m].v.x = -.71; L[m++].v.y = .71;
    sort(L, L+m);
    int first = 0, last = 0; q[0] = L[0];
    for (int i=1; i<m; ++i) {
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
    for (int i=0; i<n; ++i) cin >> u[i] >> v[i] >> w[i];
    for (int i=0; i<n; ++i) cout << (judge(i) ? "Yes" : "No") << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n) solve();
    return 0;
}