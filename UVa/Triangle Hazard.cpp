/**
 * UVa12165/LA4413
 * 三角形难题
 * Kuala Lumpur 2008
 */

#include <iostream>
#include <iomanip>
using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
} p, q, r, a, b, c;
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

double m1, m2, m3, m4, m5, m6;

void solve() {
    cin >> p.x >> p.y >> q.x >> q.y >> r.x >> r.y >> m1 >> m2 >> m3 >> m4 >> m5 >> m6;
    double t = m2*m4*m6 - m1*m3*m5;
    a = r + (r-p) * ((m1*m3 + (m1+m2)*m4)*m5 / t);
    b = p + (p-q) * ((m3*m5 + (m3+m4)*m6)*m1 / t);
    c = q + (q-r) * ((m5*m1 + (m5+m6)*m2)*m3 / t);
    cout << a.x << ' ' << a.y << ' ' << b.x << ' ' << b.y << ' ' << c.x << ' ' << c.y << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(8);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
