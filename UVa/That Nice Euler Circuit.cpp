/**
 * UVa1342/LA3263
 * 好看的一笔画
 * Shanghai 2004
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define eps 1e-10
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y){}
};
typedef Point Vector;

Vector operator+ (Vector A, Vector B) {
    return Vector(A.x + B.x, A.y + B.y);
}
 
Vector operator- (Point A, Point B) {
    return Vector(A.x - B.x, A.y - B.y);
}
 
Vector operator* (Vector A, double p) {
    return Vector(A.x * p, A.y * p);
}
 
Vector operator/ (Vector A, double p) {
    return Vector(A.x / p, A.y / p);
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

Point GetLineIntersection(Point P, Vector v, Point Q, Vector w) {
    Vector u = P - Q;
    double t = Cross(w, u) / Cross(v, w);
    return P + v * t;
}
 
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
 
bool OnSegment(Point p, Point a1, Point a2) {
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}

#define N 305
int n, kase = 0; Point p[N], v[N*N];

void solve() {
    for (int i=0; i<n; ++i) cin >> p[i].x >> p[i].y, v[i] = p[i];
    int c = --n, e = n;
    for (int i=0; i<n; i++) for (int j=i+1; j<n; j++)
        if (SegmentProperIntersection(p[i], p[i+1], p[j], p[j+1]))
            v[c++] = GetLineIntersection(p[i], p[i+1] - p[i], p[j], p[j+1] - p[j]);
    sort(v, v+c); c = unique(v, v+c) - v;
    for (int i=0; i<c; i++) for (int j=0; j<n; j++) if (OnSegment(v[i], p[j], p[j+1])) ++e;
    cout << "Case " << ++kase << ": There are " << e+2-c << " pieces." << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) solve();
    return 0;
}