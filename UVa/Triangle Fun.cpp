/**
 * UVa11437
 * 三角形趣题
 */

#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
} a, b, c;
typedef Point Vector;

Vector operator- (const Vector& A, const Vector& B) {
    return Vector(A.x - B.x, A.y - B.y);
}

double Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

int solve() {
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    return abs(Cross(b-a, c-a))/14 + .5;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}