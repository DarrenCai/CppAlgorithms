/**
 * UVa10256
 * 点集划分
 */

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define eps 1e-10
struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
};
typedef Point Vector;
 
Vector operator- (Point A, Point B) {
    return Vector(A.x - B.x, A.y - B.y);
}
 
bool operator< (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
 
int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0 ? -1 : 1);
}

bool operator== (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}

double Dot(Vector A, Vector B) {
    return A.x * B.x + A.y * B.y;
}
 
double Cross(Vector A, Vector B) {
    return A.x * B.y - A.y * B.x;
}

bool OnSegment(Point p, Point a1, Point a2) {
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) <= 0;
}

bool SegmentIntersect(Point a1, Point a2, Point b1, Point b2) {
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) <= 0 && dcmp(c3) * dcmp(c4) <= 0;
}

#define N 502
Point p[N], q[N], x[N], y[N]; int m, n;

int ConvexHull(Point* p, int n, Point* ch) {
    sort(p, p+n);
    int m = 0;
    for (int i=0; i<n; ++i) {
        while (m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) --m;
        ch[m++] = p[i];
    }
    for (int i=n-2, k=m; i>=0; --i) {
        while (m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) --m;
        ch[m++] = p[i];
    }
    if (n > 1) --m;
    return m;
}

bool PointInPolygon(Point p, Point* poly, int n) {
    int wn = 0;
    for(int i=0; i<n; ++i) {
        if (OnSegment(p, poly[i], poly[(i+1)%n])) return true;
        int k = dcmp(Cross(poly[(i+1)%n]-poly[i], p-poly[i]));
        int d1 = dcmp(poly[i].y - p.y);
        int d2 = dcmp(poly[(i+1)%n].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    return wn;
}

bool solve() {
    for (int i=0; i<m; ++i) cin >> p[i].x >> p[i].y;
    for (int i=0; i<n; ++i) cin >> q[i].x >> q[i].y;
    if (!m || !n) return true;
    int a = ConvexHull(p, m, x), b = ConvexHull(q, n, y);
    if (a < 3) {
        if (b == 1) return a<2 ? !(x[0] == y[0]) : !OnSegment(y[0], x[0], x[1]);
        if (b == 2) return a<2 ? !OnSegment(x[0], y[0], y[1]) : !SegmentIntersect(x[0], x[1], y[0], y[1]);
        if (PointInPolygon(x[0], y, b)) return false;
        if (a < 2) return true;
        if (PointInPolygon(x[1], y, b)) return false;
        for (int i=0; i<b; ++i) if (SegmentIntersect(x[0], x[1], y[i], y[i+1==b ? 0 : i+1])) return false;
    } else {
        if (PointInPolygon(y[0], x, a)) return false;
        if (b < 2) return true;
        for (int i=0; i<a; ++i) for (int j=0; j<b; ++j)
            if (SegmentIntersect(x[i], x[i+1==a ? 0 : i+1], y[j], y[j+1==b ? 0 : j+1])) return false;
        if (b > 2) for (int i=0; i<a; ++i) if (PointInPolygon(x[i], y, b)) return false;
        for (int i=0; i<b; ++i) if (PointInPolygon(y[i], x, a)) return false;
    }
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> m >> n && (m || n)) cout << (solve() ? "Yes" : "No") << endl;
    return 0;
}