/**
 * UVa1488/LA5100
 * 阴影
 * Fuzhou 2010
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

#define N 102
struct Point {
    double x, y;
    Point(double x = 0., double y = 0.): x(x), y(y) {}
} p[N];
typedef Point Vector;

Vector operator- (const Vector& A, const Vector& B) {
    return Vector(A.x - B.x, A.y - B.y);
}

bool operator< (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

double Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

double x[N], y[N], z[N], a, b, c, d; int ch[N], n;

double area(int n) {
    double area = p[ch[0]].y * (p[ch[n-1]].x - p[ch[1]].x) + p[ch[n-1]].y * (p[ch[n-2]].x - p[ch[0]].x);
    for (int i=n-2; i>0; --i) area += p[ch[i]].y * (p[ch[i-1]].x - p[ch[i+1]].x);
    return area/2.;
}

void solve() {
    cin >> n;
    for (int i=0; i<=n; ++i) cin >> x[i] >> y[i] >> z[i];
    if (a*x[n]+b*y[n]+c*z[n]-d < 0.) a *= -1., b*=-1., c*= -1., d*=-1.;
    if (a) {
        d /= a; x[n] -= d;
        for (int i=0; i<n; ++i) x[i] -= d;
    } else if (b) {
        d /= b; y[n] -= d;
        for (int i=0; i<n; ++i) y[i] -= d;
    } else {
        d /= c; z[n] -= d;
        for (int i=0; i<n; ++i) z[i] -= d;
    }
    if (a || b) {
        double r = sqrt(a*a+b*b); b /= r; a /= r;
        for (int i=0; i<=n; ++i) d = x[i], x[i] = x[i]*b - y[i]*a, y[i] = y[i]*b + d*a;
        d = sqrt(r*r + c*c); b = c/d; a = r/d;
        for (int i=0; i<=n; ++i) d = y[i], y[i] = y[i]*b - z[i]*a, z[i] = z[i]*b + d*a;
    }
    int m = 0;
    for (int i=0; i<n; ++i) if (z[i] >= z[n]) ++m;
    if (m == n) {
        cout << 0. << endl; return;
    }
    if (m) {
        cout << "Infi" << endl; return;
    }
    for (int i=0; i<n; ++i) d = z[n]-z[i], p[i].x = (z[n]*x[i]-z[i]*x[n])/ d, p[i].y = (z[n]*y[i]-z[i]*y[n]) / d;
    sort(p, p+n);
    for (int i=m=0; i<n; ++i) {
        while (m > 1 && Cross(p[ch[m-1]]-p[ch[m-2]], p[i]-p[ch[m-2]]) <= 0) --m;
        ch[m++] = i;
    }
    for (int i=n-2, k=m; i>=0; --i) {
        while (m > k && Cross(p[ch[m-1]]-p[ch[m-2]], p[i]-p[ch[m-2]]) <= 0) --m;
        ch[m++] = i;
    }
    cout << area(m) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(2);
    while (cin >> a >> b >> c >> d && (a || b || c)) solve();
    return 0;
}