/**
 * UVa10794
 * 导弹的距离
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Point3 {
    double x, y, z;
    Point3(double x = 0., double y = 0., double z = 0.): x(x), y(y), z(z) {}
} p1, p2, q1, q2;
typedef Point3 Vector3;

Vector3 operator- (const Vector3& A, const Vector3& B) {
    return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
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

double solve() {
    int _;
    cin >> _ >> p1.x >> p1.y >> p1.z >> p2.x >> p2.y >> p2.z >> q1.x >> q1.y >> q1.z >> q2.x >> q2.y >> q2.z;
    Vector3 u = p1 - q1, v = q2 - q1 - (p2 - p1);
    if (Dot(u, v) <= 0.) return Length(u);
    return Length(Cross(u, v)) / Length(v);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    int t; cin >> t;
    for (int i=1; i<=t; ++i) cout << "Case " << i << ": " << solve() << endl;
    return 0;
}