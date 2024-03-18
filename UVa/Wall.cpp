/**
 * UVa1303/LA2453
 * 围墙
 * NEERC 2001
 */

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define N 1002
struct Point {
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y) {}
    bool operator< (const Point& r) const {
        return x < r.x || (x == r.x && y < r.y);
    }
} p[N];
typedef Point Vector;

Vector operator- (const Vector& A, const Vector& B) {
    return Vector(A.x - B.x, A.y - B.y);
}

int Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

int ch[N], m, n, L, kase = 0; double pi2 = M_PI + M_PI;

double len(const Point& a, const Point& b) {
    int dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

void solve() {
    cin >> n >> L;
    for (int i=0; i<n; ++i) cin >> p[i].x >> p[i].y;
    sort(p, p+n);
    for (int i=m=0; i<n; ++i) {
        while (m > 1 && Cross(p[ch[m-1]]-p[ch[m-2]], p[i]-p[ch[m-2]]) <= 0) --m;
        ch[m++] = i;
    }
    for (int i=n-2, k=m; i>=0; --i) {
        while (m > k && Cross(p[ch[m-1]]-p[ch[m-2]], p[i]-p[ch[m-2]]) <= 0) --m;
        ch[m++] = i;
    }
    double s = pi2 * L;
    for (int i=1; i<m; ++i) s += len(p[ch[i-1]], p[ch[i]]);
    if (kase++) cout << endl;
    cout << (long long)(s + 0.5) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}