/**
 * UVa12307
 * 最小包围盒
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

struct Point {
    double x, y;
    Point(double x = 0., double y = 0.): x(x), y(y) {}
    void Normalize() {
        double l = sqrt(x*x + y*y); x /= l; y /= l;
    }
};
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

double Dot(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

#define N 100100
Point p[N]; int ch[N<<1], m, n;

void solve() {
    for (int i=0; i<n; ++i) cin >> p[i].x >> p[i].y;
    sort(p, p+n);
    for (int i=m=0; i<n; ++i) {
        while (m > 1 && Cross(p[ch[m-1]]-p[ch[m-2]], p[i]-p[ch[m-2]]) <= 0.) --m;
        ch[m++] = i;
    }
    for (int i=n-2, k=m; i>=0; --i) {
        while (m > k && Cross(p[ch[m-1]]-p[ch[m-2]], p[i]-p[ch[m-2]]) <= 0.) --m;
        ch[m++] = i;
    }
    n = --m;
    for (int i=0; i<n; ++i) ch[m++] = ch[i];
    double a = 1e12, s = 1e8;
    for (int i=0, h=1, j=0, k=0; i<n; ++i) {
        Vector v = p[ch[i+1]] - p[ch[i]]; v.Normalize();
        while (Cross(v, p[ch[h+1]] - p[ch[h]]) > 0.) ++h;
        while (Dot(v, p[ch[j+1]] - p[ch[j]]) > 0.) ++j;
        for (k = max(j, k); Dot(v, p[ch[k+1]] - p[ch[k]]) <= 0.; ++k);
        double c = Cross(v, p[ch[h]] - p[ch[i]]), d = Dot(v, p[ch[j]] - p[ch[i]]) - Dot(v, p[ch[k]] - p[ch[i]]);
        a = min(a, c*d); s = min(s, 2.*(c+d));
    }
    cout << a << ' ' << s << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(2);
    while (cin >> n && n) solve();
    return 0;
}