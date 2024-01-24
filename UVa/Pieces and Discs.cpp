/**
 * UVa12296
 * 块和圆盘
 */

#include <iostream>
#include <iomanip>
#include <cstring>
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

Vector operator+ (const Vector& A, const Vector& B) {
    return Vector(A.x + B.x, A.y + B.y);
}

Vector operator- (const Vector& A, const Vector& B) {
    return Vector(A.x - B.x, A.y - B.y);
}

Vector operator* (const Vector& A, double p) {
    return Vector(A.x * p, A.y * p);
}

int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0. ? -1 : 1);
}

bool operator== (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}

double Dot(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

double Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

bool SegmentProperIntersect(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

bool OnSegment(const Point& p, const Point& a1, const Point& a2) {
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) <= 0;
}

double LineInterp(const Point& P, const Vector& v, const Point& Q, const Vector& w) {
    Vector u = P - Q;
    return Cross(w, u) / Cross(v, w);
}

#define N 26
Point x[N], y[N], p[N*N]; int g[N*N][N<<1], c[N*N], m, n, l, w, s, t; double q[N*N]; bool vis[N*N][N<<1];

int addPoint(const Point& x) {
    for (int i=0; i<t; ++i) if (p[i] == x) return i;
    p[t] = x;
    return t++;
}

struct {
    int v[N], n; double s;
    void calc() {
        s = p[v[0]].y * (p[v[n-1]].x - p[v[1]].x) + p[v[n-1]].y * (p[v[n-2]].x - p[v[0]].x);
        for(int i=n-2; i>0; --i) s += p[v[i]].y * (p[v[i-1]].x - p[v[i+1]].x);
        s *= .5;
    }
    bool overlaps(const Point& c, double r) const {
        double r2 = r*r; int wn = 0;
        for (int i=0; i<n; ++i) {
            const Point &a = p[v[i]], &b = p[v[i+1 < n ? i+1 : 0]];
            if (dcmp(Dot(a-c, a-c) - r2) < 0) return true;
            Vector d = b - a, e = c-a;  double f = Dot(e, d), g = Dot(d, d);
            if (dcmp(f) > 0 && dcmp(f-g) < 0) {
                Point x = a + d * (f/g);
                if (dcmp(Dot(x-c, x-c) - r2) < 0) return true;
            }
            if (OnSegment(c, a, b)) return true;
            int k = dcmp(Cross(d, e));
            int d1 = dcmp(a.y - c.y);
            int d2 = dcmp(b.y - c.y);
            if (k > 0 && d1 <= 0 && d2 > 0) wn++;
            if (k < 0 && d2 <= 0 && d1 > 0) wn--;
        }
        return wn;
    }
} poly[N*N];

struct nex {
    int i; double a;
    bool operator< (const nex& rhs) const {
        return a > rhs.a;
    }
};

void dfs(int u, int i, int a) {
    if (vis[u][i]) return;
    vis[u][i] = 1;
    int v = g[u][i];
    if (u == a) poly[s].n = 0;
    poly[s].v[poly[s].n++] = v;
    if (v != a) {
        Vector d = p[v] - p[u]; d.Normalize();
        int n = 0; nex nx[N];
        for (int j=0; j<c[v]; ++j) if (g[v][j] != u) {
            Vector e = p[g[v][j]] - p[v]; e.Normalize();
            nx[n].i = j; nx[n++].a = Cross(d, e) > 0. ? 1. - Dot(d, e) : Dot(d, e) - 1.;
        }
        sort(nx, nx+n);
        if (nx[0].a < 0.) return;
        dfs(v, nx[0].i, a);
        for (int j=1; j<n; ++j) dfs(v, nx[j].i, v);
    } else poly[s++].calc();
}

void solve() {
    memset(c, t = 0, sizeof(c)); memset(vis, 0, sizeof(vis));
    for (int i=0; i<n; ++i) cin >> x[i].x >> x[i].y >> y[i].x >> y[i].y;
    q[0] = 0.; q[1] = l; s = 2;
    for (int i=0; i<n; ++i) {
        if (x[i].y == 0.) q[s++] = x[i].x;
        if (y[i].y == 0.) q[s++] = y[i].x;
    }
    sort(q, q+s); s = unique(q, q+s) - q;
    for (int i=1; i<s; ++i) {
        int u = addPoint(Point(q[i-1], 0.)), v = addPoint(Point(q[i], 0.));
        g[u][c[u]++] = v; g[v][c[v]++] = u;
    }
    q[0] = 0.; q[1] = w; s = 2;
    for (int i=0; i<n; ++i) {
        if (x[i].x == l) q[s++] = x[i].y;
        if (y[i].x == l) q[s++] = y[i].y;
    }
    sort(q, q+s); s = unique(q, q+s) - q;
    for (int i=1; i<s; ++i) {
        int u = addPoint(Point(l, q[i-1])), v = addPoint(Point(l, q[i]));
        g[u][c[u]++] = v; g[v][c[v]++] = u;
    }
    q[0] = 0.; q[1] = l; s = 2;
    for (int i=0; i<n; ++i) {
        if (x[i].y == w) q[s++] = x[i].x;
        if (y[i].y == w) q[s++] = y[i].x;
    }
    sort(q, q+s); s = unique(q, q+s) - q;
    for (int i=1; i<s; ++i) {
        int u = addPoint(Point(q[i-1], w)), v = addPoint(Point(q[i], w));
        g[u][c[u]++] = v; g[v][c[v]++] = u;
    }
    q[0] = 0.; q[1] = w; s = 2;
    for (int i=0; i<n; ++i) {
        if (x[i].x == 0.) q[s++] = x[i].y;
        if (y[i].x == 0.) q[s++] = y[i].y;
    }
    sort(q, q+s); s = unique(q, q+s) - q;
    for (int i=1; i<s; ++i) {
        int u = addPoint(Point(0, q[i-1])), v = addPoint(Point(0, q[i]));
        g[u][c[u]++] = v; g[v][c[v]++] = u;
    }
    for (int i=0; i<n; ++i) {
        q[0] = 0.; q[1] = 1.; s = 2; Vector d = y[i] - x[i];
        for (int j=0; j<n; ++j) if (i!=j && SegmentProperIntersect(x[i], y[i], x[j], y[j]))
            q[s++] = LineInterp(x[i], d, x[j], y[j]-x[j]);
        sort(q, q+s); s = unique(q, q+s) - q;
        for (int j=1; j<s; ++j) {
            int u = addPoint(x[i]+d*q[j-1]), v = addPoint(x[i]+d*q[j]);
            g[u][c[u]++] = v; g[v][c[v]++] = u;
        }
    }
    dfs(s = 0, 0, 0);
    while (m--) {
        double r; cin >> x[0].x >> x[0].y >> r;
        for (int i=n=0; i<s; ++i) {
            if (poly[i].overlaps(x[0], r)) {
                q[n++] = poly[i].s;
            }
        }
        sort(q, q+n);
        cout << n;
        for (int i=0; i<n; ++i) cout << ' ' << q[i];
        cout << endl;
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(2);
    while (cin>>n>>m>>l>>w && n) solve();
    return 0;
}