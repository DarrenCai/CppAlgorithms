/**
 * UVa11796
 * 狗的距离
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define eps 1e-10
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y){}
};
typedef Point Vector;

Vector operator+ (Vector A, Vector B) {
    return Vector(A.x + B.x, A.y + B.y);
}
 
Vector operator- (Point A, Point B) {
    return Vector(A.x - B.x, A.y - B.y);
}
 
Vector operator* (Vector A, double p) {
    return Vector(A.x * p, A.y * p);
}
 
Vector operator/ (Vector A, double p) {
    return Vector(A.x / p, A.y / p);
}
 
bool operator< (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
 
int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0 ? -1 : 1);
}
 
bool operator== (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
 
double Dot(Vector A, Vector B) {
    return A.x * B.x + A.y * B.y;
}
 
double Length(Vector A) {
    return sqrt(Dot(A, A));
}
 
double Cross(Vector A, Vector B) {
    return A.x * B.y - A.y * B.x;
}

double DistanceToSegment(Point P, Point A, Point B) {
    if(A == B) return Length(P-A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if(dcmp(Dot(v1, v3)) > 0) return Length(v3);
    else return abs(Cross(v1, v2)) / Length(v1);
}

#define N 52
Point a[N], b[N]; int m, n; double mind, maxd;

void solve(int kase) {
    cin >> m >> n;
    for (int i=0; i<m; ++i) cin >> a[i].x >> a[i].y;
    for (int i=0; i<n; ++i) cin >> b[i].x >> b[i].y;
    double lenA = 0., lenB = 0.; Point A = a[0], B = b[0]; mind = 1e9; maxd = 0.;
    for (int i=1; i<m; ++i) lenA += Length(a[i]-a[i-1]);
    for (int i=1; i<n; ++i) lenB += Length(b[i]-b[i-1]);
    for (int i=1, j=1; i<m && j<n;) {
        double La = Length(a[i]-A), Lb = Length(b[j]-B), t = min(La/lenA, Lb/lenB);
        Vector Va = (a[i]-A) * (t*lenA/La), Vb = (b[j]-B) * (t*lenB/Lb), C = B + Vb - Va;
        mind = min(mind, DistanceToSegment(A, B, C)); maxd = max(maxd, max(Length(B-A), Length(C-A)));
        A = A + Va; B = B + Vb;
        if (A == a[i]) ++i;
        if (B == b[j]) ++j;
    }
    cout << "Case " << kase << ": " << maxd - mind << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(0);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) solve(kase);
    return 0;
}