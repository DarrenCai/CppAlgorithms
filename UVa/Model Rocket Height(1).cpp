/**
 * UVa1360/LA3500
 * North America - Greater NY 2005
 */

#include <iostream>
#include <cmath>
using namespace std;

struct Point3 {
    double x, y, z;
    Point3(double x = 0., double y = 0., double z = 0.): x(x), y(y), z(z) {}
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

double Dot(const Vector3& A, const Vector3& B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

Vector3 Cross(const Vector3& A, const Vector3& B) {
    return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
}

#define dtr 0.01745329251994329508887757483
double a, b, c, d; int n; Point3 A, B, C; Vector3 u, v, w;

int solve() {
    cin >> a >> b >> c >> d;
    a *= dtr; b *= dtr; c *= dtr; d *= dtr; double x = 100./sin(d-c), y = x*sin(c), z = x*sin(d);
    v.x = z*cos(c); v.y = z*sin(c); v.z = z*tan(a); w.x = y*cos(d); w.y = y*sin(d); w.z = y*tan(b);
    Vector3 norm = Cross(v, w); x = Length(norm); norm.x /= x; norm.y /= x; norm.z /= x;
    x = Dot(u, norm); norm.x *= x; norm.y *= x; norm.z *= x; C = A - norm;
    C = C + v * (Length(Cross(w, C - B)) / Length(Cross(v, w)));
    return C.z + .5*norm.z + .5;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cin >> n >> A.z >> B.z; A.x = -50.; B.x = 50.; u = A - B;
    for (int i=1; i<=n; ++i) cout << i << ": " << solve() << endl;
    return 0;
}