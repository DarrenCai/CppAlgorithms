/**
 * UVa1100/LA4795
 * 压纸器
 * World Finals 2010
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define eps 1e-8 // 有点卡阈值，#define eps 1e-10 就是WA了
struct Point3 {
    double x, y, z;
    Point3(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
    void Normalize() {
        double l = sqrt(x*x + y*y + z*z); x /= l; y /= l; z /= l;
    }
} p[5], f, q;
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

Vector3 operator/ (const Vector3& A, double p) {
    return Vector3(A.x / p, A.y / p, A.z / p);
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

double Angle(const Vector3& A, const Vector3& B) {
    return acos(Dot(A, B) / Length(A) / Length(B));
}

int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0. ? -1 : 1);
}

double DistanceToLine(const Point3& P, const Point3& A, const Point3& B) {
    Vector3 v1 = B - A, v2 = P - A;
    return Length(Cross(v1, v2)) / Length(v1);
}

double DistanceToPlane(const Point3& p, const Point3& p0, const Vector3& n) {
    return fabs(Dot(p-p0, n));
}

Point3 GetPlaneProjection(const Point3& p, const Point3& p0, const Vector3& n) {
    return p-n*Dot(p-p0, n);
}

bool PointInTri(const Point3& p, const Point3& p0, const Point3& p1, const Point3& p2) {
    double s = Length(Cross(p-p0, p1-p0)) + Length(Cross(p-p0, p2-p0)) + Length(Cross(p-p1, p2-p1));
    return dcmp(s - Length(Cross(p1-p0, p2-p0))) == 0;
}

double x, y; int kase = 0;

bool judge(const Point3& p, const Point3& a, const Point3& b, const Point3& c) {
    return PointInTri(p, a, b, c) && DistanceToLine(p, a, b)>=0.2 &&
        DistanceToLine(p, a, c)>=0.2 && DistanceToLine(p, b, c)>=0.2;
}

bool judge(const Point3& p, const Point3& a, const Point3& b, const Point3& c, const Point3& d) {
    return (PointInTri(p, a, c, b) || PointInTri(p, a, c, d)) && DistanceToLine(p, a, b)>=0.2 &&
        DistanceToLine(p, b, c)>=0.2 && DistanceToLine(p, c, d)>=0.2 && DistanceToLine(p, d, a)>=0.2;
}

bool solve() {
    cin >> p[0].x; x = 1e6; y = 0.;
    if (cin.peek() != ' ') return false;
    cin >> p[0].y >> p[0].z >> p[1].x >> p[1].y >> p[1].z >> p[2].x >> p[2].y >> p[2].z
        >> p[3].x >> p[3].y >> p[3].z >> p[4].x >> p[4].y >> p[4].z >> f.x >> f.y >> f.z;
    Vector3 v = Cross(p[1]-p[0], p[2]-p[0]); double s = abs(Dot(v, p[3]-p[0])), t = abs(Dot(v, p[4]-p[0]));
    q = ((p[0] + p[1] + p[2] + p[3]) * s + (p[0] + p[1] + p[2] + p[4]) * t) / (4 * (s + t));
    for (int i=0; i<5; ++i) for (int j=i+1; j<5; ++j) for (int k=j+1; k<5; ++k) {
        int a, b;
        for (a=0; a<5; ++a) if (a!=i && a!=j && a!=k) {
            b = 10-i-j-k-a; break;
        }
        Vector3 n = Cross(p[j]-p[i], p[k]-p[i]);
        int d1 = dcmp(Dot(n, p[a]-p[i])), d2 = dcmp(Dot(n, p[b]-p[i]));
        if (d1 * d2 < 0) continue;
        n.Normalize();
        Point3 r = GetPlaneProjection(q, p[i], n);
        bool ok = judge(r, p[i], p[j], p[k]);
        if (!ok) {
            if (d1 == 0) {
                if (!judge(r, p[i], p[k], p[j], p[a])) continue;
            } else if (d2 == 0) {
                if (!judge(r, p[i], p[k], p[j], p[b])) continue;
            } else continue;
        }
        double d = DistanceToPlane(f, p[i], n);
        x = min(x, d); y = max(y, d);
    }
    cout << "Case " << ++kase << ": " << x << ' ' << y << endl;
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(5);
    while (solve());
    return 0;
}