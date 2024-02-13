/**
 * UVa11817
 * 地球隧道
 */

#include <iostream>
#include <math.h>
using namespace std;

#define R 6371009.
#define dtr 0.017453292519943295
struct Point3 {
    double x, y, z;
    Point3(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
};
typedef Point3 Vector3;

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

void solve() {
    double lat0, lng0, lat1, lng1; cin >> lat0 >> lng0 >> lat1 >> lng1;
    lat0 *= dtr; lng0 *= dtr; lat1 *= dtr; lng1 *= dtr;
    double c0 = R*cos(lat0), c1 = R*cos(lat1);
    Point3 a(c0*cos(lng0), c0*sin(lng0), R*sin(lat0)), b(c1*cos(lng1), c1*sin(lng1), R*sin(lat1));
    cout << int(R*acos(Dot(a, b)/R/R) - Length(a-b) + .5) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}