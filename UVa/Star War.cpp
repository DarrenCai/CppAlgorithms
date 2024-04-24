/**
 * UVa11836
 * 星球大战
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define eps 1e-8
struct Point3 {
    double x, y, z;
    Point3(double x = 0., double y = 0., double z = 0.): x(x), y(y), z(z) {}
} p[4], q[4];
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

int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0. ? -1 : 1);
}

bool operator== (const Point3& a, const Point3& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0 && dcmp(a.z - b.z) == 0;
}

double Length(const Vector3& A) {
    return sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
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

double DistanceToSegment(const Point3& P, const Point3& A, const Point3& B) {
    if (A == B) return Length(P-A);
    Vector3 v1 = B - A, v2 = P - A, v3 = P - B;
    if (dcmp(Dot(v1, v2)) < 0) return Length(v2);
    if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
    return Length(Cross(v1, v2)) / Length(v1);
}

bool PointInTri(const Point3& P, const Point3& A, const Point3& B, const Point3& C) {
    double s = Length(Cross(P-A, B-A)) + Length(Cross(P-B, C-B)) + Length(Cross(P-C, A-C));
    double t = Length(Cross(B-A, C-A));
    return dcmp(s - Length(Cross(B-A, C-A))) == 0;
}

double DisToTri(const Point3& P, const Point3& A, const Point3& B, const Point3& C) {
    Vector3 n = Cross(B-A, C-A), v = P - A; double l = Length(n); n.x /= l; n.y /= l; n.z /= l;
    double d = Dot(n, v); Point3 r = v - n*d + A;
    if (PointInTri(r, A, B, C)) return abs(d);
    return min(min(DistanceToSegment(P, A, B), DistanceToSegment(P, A, C)), DistanceToSegment(P, B, C));
}

double SegDis(const Point3& A, const Point3& B, const Point3& C, const Point3& D) {
    Vector3 n = Cross(B-A, D-C), v = A-C, w = B-C; double l = Length(n); n.x /= l; n.y /= l; n.z /= l;
    double d = Dot(n, v); Point3 a = v - n*d + C, b = w - n*d + C;
    if (SegmentProperIntersect(a, b, C, D)) return abs(d);
    return min(min(DistanceToSegment(A, C, D), DistanceToSegment(B, C, D)),
                min(DistanceToSegment(C, A, B), DistanceToSegment(D, A, B)));
}

double solve() {
    double d = 1e4;
    for (int i=0; i<4; ++i) cin >> p[i].x >> p[i].y >> p[i].z;
    for (int i=0; i<4; ++i) {
        cin >> q[i].x >> q[i].y >> q[i].z;
        d = min(d, min(DisToTri(q[i], p[0], p[1], p[2]), DisToTri(q[i], p[0], p[1], p[3])));
        d = min(d, min(DisToTri(q[i], p[0], p[2], p[3]), DisToTri(q[i], p[1], p[2], p[3])));
    }
    for (int i=0; i<4; ++i) {
        d = min(d, min(DisToTri(p[i], q[0], q[1], q[2]), DisToTri(p[i], q[0], q[1], q[3])));
        d = min(d, min(DisToTri(p[i], q[0], q[2], q[3]), DisToTri(p[i], q[1], q[2], q[3])));
        for (int j=i+1; j<4; ++j) for (int a=0; a<3; ++a) for (int b=a+1; b<4; ++b)
            d = min(d, SegDis(p[i], p[j], q[a], q[b]));
    }
    return d;
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