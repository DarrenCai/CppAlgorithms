/**
 * UVa1433/LA4371
 * 空气动力学
 * NEERC 2008
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

#define N 102
struct Point {
    double x, y;
    Point(double x = 0., double y = 0.): x(x), y(y) {}
} p[N*N>>2];
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

int ch[N*N>>2], x[N], y[N], z[N], a[N], z0, z1, n, kase = 0;

bool cmp(int i, int j) {
    return z[i] < z[j];
}

double area(int n) {
    double area = p[ch[0]].y * (p[ch[n-1]].x - p[ch[1]].x) + p[ch[n-1]].y * (p[ch[n-2]].x - p[ch[0]].x);
    for (int i=n-2; i>0; --i) area += p[ch[i]].y * (p[ch[i-1]].x - p[ch[i+1]].x);
    return area/2;
}

void solve() {
    if (kase++) cout << endl;
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i] >> z[i], a[i] = i;
    sort(a, a+n, cmp);
    for (int i=z0, j=0; i<=z1; ++i) {
        while (j<n && z[a[j]]<i) ++j;
        int t = 0, k = j;
        while (j<n && z[a[j]]==i) p[t].x = x[a[j]], p[t++].y = y[a[j++]];
        if (k>0 && j<n) for (int b=0; b<k; ++b) for (int c=j; c<n; ++c) {
            double d = z[a[c]] - z[a[b]];
            p[t].x = ((i-z[a[b]])*x[a[c]] + (z[a[c]]-i)*x[a[b]])/d;
            p[t++].y = ((i-z[a[b]])*y[a[c]] + (z[a[c]]-i)*y[a[b]])/d;
        }
        sort(p, p+t);
        for (int i=k=0; i<t; ++i) {
            while (k > 1 && Cross(p[ch[k-1]]-p[ch[k-2]], p[i]-p[ch[k-2]]) <= 0) --k;
            ch[k++] = i;
        }
        for (int i=t-2, m=k; i>=0; --i) {
            while (k > m && Cross(p[ch[k-1]]-p[ch[k-2]], p[i]-p[ch[k-2]]) <= 0) --k;
            ch[k++] = i;
        }
        if (t > 1) --k;
        k > 2 ? cout << area(k) << endl : cout << 0. << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(5);
    while (cin >> n >> z0 >> z1) solve();
    return 0;
}