/**
 * UVa1318/LA2797
 * 怪物陷阱
 * Aizu 2003
 */

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define eps 1e-10
struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    void Normalize() {
        double l = sqrt(x*x + y*y); x /= l; y /= l;
    }
};
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

bool operator< (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

double Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

double Dot(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0. ? -1 : 1);
}

int sign(double x) {
    return x==0. ? 0 : (x < 0. ? -1 : 1);
}

bool SegmentProperIntersect(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return sign(c1) * sign(c2) < 0 && sign(c3) * sign(c4) < 0;
}

bool OnSegment(const Point& p, const Point& a1, const Point& a2) {
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}

#define N 205
Point p[N]; int x[N], q[N], n, t; bool vis[N];

bool NotOnAnySegment(const Point& x) {
    for (int i=0; i<n; ++i) if (OnSegment(x, p[i], p[i+n])) return false;
    return true;
}

bool NotIntersectWithAnySegment(int u, int v) {
    for (int i=0; i<n; ++i) if (SegmentProperIntersect(p[i], p[i+n], p[u], p[v])) return false;
    return true;
}

bool solve() {
    memset(vis, t = 0, sizeof(vis));
    for (int i=0; i<n; ++i) {
        cin >> p[i].x >> p[i].y >> p[i+n].x >> p[i+n].y;
        Vector v = p[i+n] - p[i]; v.Normalize(); v = v*1e-6;
        p[i].x -= v.x; p[i].y -= v.y; p[i+n].x += v.x; p[i+n].y += v.y;
    }
    p[n<<1].x = p[n<<1].y = 0.; p[(n<<1)+1].x = -60.; p[(n<<1)+1].y = 60.; x[t++] = n<<1; x[t++] = (n<<1)+1;
    for (int i=0; i<n; ++i) {
        if (NotOnAnySegment(p[i])) x[t++] = i;
        if (NotOnAnySegment(p[i+n])) x[t++] = i+n;
    }
    int head = 0, tail = 1; q[0] = 0;
    while (head < tail) {
        int u = q[head++];
        for (int v=1; v<t; ++v) if (!vis[v] && NotIntersectWithAnySegment(x[u], x[v])) {
            if (v == 1) return false;
            vis[q[tail++] = v] = 1;
        }
    }
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n) cout << (solve() ? "yes" : "no") << endl;
    return 0;
}