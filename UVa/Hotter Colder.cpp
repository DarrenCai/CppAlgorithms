/**
 * UVa10084
 * 更冷更热
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

#define eps 1e-10
struct Point {
    double x, y;
    Point(double x = 0., double y = 0.): x(x), y(y) {}
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

double Dot(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

Point GetLineIntersection(const Point& P, const Vector& v, const Point& Q, const Vector& w) {
    Vector u = P - Q;
    return P + v * (Cross(w, u) / Cross(v, w));
}

int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0. ? -1 : 1);
}

bool OnSegment(const Point& p, const Point& a1, const Point& a2) {
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}

double Area(const Point* p, int n) {
    if (n < 3) return 0.;
    double area = p[0].y * (p[n-1].x - p[1].x) + p[n-1].y * (p[n-2].x - p[0].x);
    for (int i=n-2; i>0; --i) area += p[i].y * (p[i-1].x - p[i+1].x);
    return area / 2.;
}

#define N 55
Point p[2][N], v[2]; char s[8]; int t[2];

void solve() {
    v[0] = p[0][0] = Point(); p[0][1] = Point(10., 0.); p[0][2] = Point(10., 10.); p[0][3] = Point(0., 10.);
    int f = 1; t[0] = t[1] = 4;
    while (cin >> v[f].x >> v[f].y >> s) {
        Point (&r)[N] = p[f^1], (&q)[N] = p[f], &u = v[f^1], &w = v[f]; int &m = t[f], &n = t[f^1];
        if (m < 3 || s[0] == 'S') {
            cout << 0. << endl; m = 0; continue;
        }
        Point A = Point((u.x + w.x) / 2., (u.y + w.y) / 2.);
        Vector v = Point(s[0]=='H' ? w.y - u.y : u.y - w.y, s[0]=='H' ? u.x - w.x : w.x - u.x);
        for (int i=m=0; i<n; ++i) {
            Point &C = r[i], &D = r[i+1<n ? i+1 : 0]; Vector d = D-C;
            if (dcmp(Cross(v, C-A)) >= 0) q[m++] = C;
            if (Cross(v, d) != 0) {
                Point ip = GetLineIntersection(A, v, C, d);
                if (OnSegment(ip, C, D)) q[m++] = ip;
            }
        }
        cout << Area(q, m) << endl;
        f ^= 1;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(2);
    solve();
    return 0;
}