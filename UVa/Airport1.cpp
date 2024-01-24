/**
 * UVa11168
 * 飞机场
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
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
 
Vector operator- (Point A, Point B) {
    return Vector(A.x - B.x, A.y - B.y);
}
 
bool operator< (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
 
int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0 ? -1 : 1);
}

double Dot(Vector A, Vector B) {
    return A.x * B.x + A.y * B.y;
}
 
double Length(Vector A) {
    return sqrt(Dot(A, A));
}
 
double Angle(Vector A, Vector B) {
    return acos(Dot(A, B) / Length(A) / Length(B));
}
 
double Cross(Vector A, Vector B) {
    return A.x * B.y - A.y * B.x;
}
 
double Area2(Point A, Point B, Point C) {
    return Cross(B - A, C - A);
}
 
Vector Rotate(Vector A, double rad) {
    return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}
 
bool OnSegment(Point p, Point a1, Point a2) { // 不含端点
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}
 
bool OnSegment2(Point p, Point a1, Point a2) { // 含端点
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) <= 0;
}

double PolygonArea(Point* p, int n) { // 有向面积
    double area = p[0].y * (p[n-1].x - p[1].x) + p[n-1].y * (p[n-2].x - p[0].x);
    for(int i=n-2; i>0; --i) area += p[i].y * (p[i-1].x - p[i+1].x);
    return area/2;
}

#define N 10020
Point p[N], ch[N];

double solve() {
    int m = 0, n; cin >> n; double x = 0., y = 0.;
    for (int i=0; i<n; ++i) cin >> p[i].x >> p[i].y, x += p[i].x, y += p[i].y;
    sort(p, p+n);
    for (int i=0; i<n; ++i) {
        while (m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) --m;
        ch[m++] = p[i];
    }
    for (int i=n-2, k=m; i>=0; --i) {
        while (m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) --m;
        ch[m++] = p[i];
    }
    if (n > 1) --m;
    if (m < 3) return 0.;
    double a = ch[m-1].y - ch[0].y, b = ch[0].x - ch[m-1].x, c = Cross(ch[m-1], ch[0]);
    double ans = abs(a*x + b*y + n*c) / sqrt(a*a + b*b);
    for (int i=1; i<m; ++i) {
        a = ch[i-1].y - ch[i].y; b = ch[i].x - ch[i-1].x; c = Cross(ch[i-1], ch[i]);
        ans = min(ans, abs(a*x + b*y + n*c) / sqrt(a*a + b*b));
    }
    return ans / n;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(3);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case #" << kase << ": " << solve() << endl;
    return 0;
}