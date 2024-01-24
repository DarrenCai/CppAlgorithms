/**
 * UVa1453/LA4728
 * 正方形
 * Seoul 2009
 */

#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y) {}
};
typedef Point Vector;
 
Vector operator- (const Point& A, const Point& B) {
    return Vector(A.x - B.x, A.y - B.y);
}
 
bool operator< (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
 
bool operator== (const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}
 
int Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

int Dot(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

#define N 400040
Point p[N], ch[N];

void solve() {
    int m = 0, n; cin >> n;
    for (int i=0; i<n; ++i) {
        int x, y, w; cin >> x >> y >> w;
        p[4*i] = Point(x, y); p[4*i+1] = Point(x, y+w); p[4*i+2] = Point(x+w, y); p[4*i+3] = Point(x+w, y+w);
    }
    sort(p, p+(n<<=2));
    n = unique(p, p+n) - p;
    for (int i=0; i<n; ++i) {
        while (m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) --m;
        ch[m++] = p[i];
    }
    int k = m;
    for (int i=n-2; i>=0; --i) {
        while (m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) --m;
        ch[m++] = p[i];
    }
    --m;
    int d = 0; Vector v;
    for (int i=0, q=max(k-1, 2); i<m; ++i) {
        while (Cross(v = ch[i+1]-ch[i], ch[q+1]-ch[i]) > Cross(v, ch[q]-ch[i])) q = (q+1) % m;
        d = max(d, max(Dot(v = ch[q]-ch[i], v), Dot(v = ch[q]-ch[i+1], v)));
    }
    cout << d << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}