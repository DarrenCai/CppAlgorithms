/**
 * UVa11800
 * 形状
 */

#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y) {}
} a, b, c, d, p;
typedef Point Vector;

Vector operator- (const Vector& A, const Vector& B) {
    return Vector(A.x - B.x, A.y - B.y);
}

int Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

int sign(const Vector& A, const Vector& B) {
    int s = Cross(A, B);
    return s == 0 ? 0 : (s > 0 ? 1 : -1);
}

int Dot(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

const char s[][24] = {"Square", "Rectangle", "Rhombus", "Parallelogram", "Trapezium", "Ordinary Quadrilateral"};

int solve() {
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
    if (sign(b-a, c-a) * sign(b-a, d-a) < 0) p = c, c = b, b = p;
    else if (sign(c-a, b-a) * sign(c-a, d-a) > 0) p = c, c = d, d = p;
    int ab = Dot(b-a, b-a), bc = Dot(c-b, c-b), cd = Dot(d-c, d-c), da = Dot(d-a, d-a);
    if (ab == bc && bc == cd && cd == da) return Dot(a-b, b-c) ? 2 : 0;
    if (ab == cd && bc == da) return Dot(a-b, b-c) ? 3 : 1;
    return Cross(a-b, c-d) && Cross(b-c, a-d) ? 5 : 4;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case " << kase << ": " << s[solve()] << endl;
    return 0;
}