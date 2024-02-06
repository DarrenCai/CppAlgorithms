/**
 * UVa11275
 * 三维三角形
 */

#include <iostream>
#include <cmath>
using namespace std;

#define eps 1e-10
struct Point3 {
    double x, y, z;
    Point3(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
    void Normalize() {
        double l = sqrt(x*x + y*y + z*z); x /= l; y /= l; z /= l;
    }
};
typedef Point3 Vector3;

Vector3 operator+ (const Vector3& A, const Vector3& B) {
    return Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
}

Vector3 operator- (const Vector3& A, const Vector3& B) {
    return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
}

Vector3 operator* (const Vector3& A, double p) {
    return Vector3(A.x * p, A.y * p, A.z * p);
}

double Length(const Vector3& A) {
    return sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
}

int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0. ? -1 : 1);
}

bool operator== (const Point3& a, const Point3& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0 && dcmp(a.z - b.z) == 0;
}

double Dot(const Vector3& A, const Vector3& B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

Vector3 Cross(const Vector3& A, const Vector3& B) {
    return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
}

bool SegmentProperIntersect(const Point3& a1, const Point3& a2, const Point3& b1, const Point3& b2) {
    Vector3 c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    Vector3 c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(Dot(c1, c2)) < 0 && dcmp(Dot(c3, c4)) < 0;
}

bool OnSegment(const Point3& p, const Point3& a1, const Point3& a2) {
    return dcmp(Length(Cross(a1 - p, a2 - p))) == 0 && dcmp(Dot(a1 - p, a2 - p)) <= 0;
}

bool SegmentIntersect(const Point3& a1, const Point3& a2, const Point3& b1, const Point3& b2) {
    if (OnSegment(a1, b1, b2) || OnSegment(a2, b1, b2) || OnSegment(b1, a1, a2) || OnSegment(b2, a1, a2)) return true;
    Vector3 v = Cross(a2-a1, b1-a1); v.Normalize();
    return dcmp(Dot(b2-a1, v)) == 0 && SegmentProperIntersect(a1, a2, b1, b2);
}

bool PointInTri(const Point3& p, const Point3& p0, const Point3& p1, const Point3& p2) {
    double s = Length(Cross(p-p0, p1-p0)) + Length(Cross(p-p0, p2-p0)) + Length(Cross(p-p1, p2-p1));
    return dcmp(s - Length(Cross(p1-p0, p2-p0))) == 0;
}

bool SegmentIntersectTri(const Point3& a1, const Point3& a2, const Point3& p0, const Point3& p1, const Point3& p2) {
    Vector3 n = Cross(p1-p0, p2-p0), v = a2 - a1; double d = Dot(n, v);
    if (dcmp(d) == 0) return false;
    double t = Dot(n, p0-a1) / d;
    return t > 0. && t < 1. && PointInTri(a1 + v*t, p0, p1, p2);
}

Point3 a, b, c, d, e, f;

int solve() {
    cin >> a.x >> a.y >> a.z >> b.x >> b.y >> b.z >> c.x >> c.y >> c.z
        >> d.x >> d.y >> d.z >> e.x >> e.y >> e.z >> f.x >> f.y >> f.z;
    return SegmentIntersect(a, b, d, e) || SegmentIntersect(a, b, d, f) || SegmentIntersect(a, b, e, f) ||
        SegmentIntersect(a, c, d, e) || SegmentIntersect(a, c, d, f) || SegmentIntersect(a, c, e, f) ||
        SegmentIntersect(b, c, d, e) || SegmentIntersect(b, c, d, f) || SegmentIntersect(b, c, e, f) ||
        PointInTri(a, d, e, f) || PointInTri(b, d, e, f) || PointInTri(c, d, e, f) || 
        PointInTri(d, a, b, c) || PointInTri(e, a, b, c) || PointInTri(f, a, b, c) ||
        SegmentIntersectTri(a, b, d, e, f) || SegmentIntersectTri(a, c, d, e, f) || SegmentIntersectTri(b, c, d, e, f) ||
        SegmentIntersectTri(d, e, a, b, c) || SegmentIntersectTri(d, f, a, b, c) || SegmentIntersectTri(e, f, a, b, c);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}