/**
 * UVa11726
 * 犯罪现场
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define eps 1e-10
struct Point {
    double x, y;
    Point(double x = 0., double y = 0.): x(x), y(y) {}
};
typedef Point Vector;

Vector operator- (const Vector& A, const Vector& B) {
    return Vector(A.x - B.x, A.y - B.y);
}

int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0. ? -1 : 1);
}

bool operator== (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}

double Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

double Dot(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

double Lsq(const Vector& A) {
    return A.x*A.x + A.y*A.y;
}

#define N 102
Point c[N], p[11*N]; double r[N], pi2 = M_PI + M_PI; int n; bool esc0[N], esc[11*N];

double solve() {
    cin >> n;
    int a = 0, b = 0;
    while (n--) {
        char ch; cin >> ch;
        if (ch == 'p') {
            int k; cin >> k;
            while (k--) cin >> p[b].x >> p[b].y, esc[b++] = false;
        } else cin >> c[a].x >> c[a].y >> r[a], esc0[a++] = false;
    }
    for (int i=0; i<a; ++i) if (!esc0[i]) for (int j=i+1; j<a; ++j) {
        if (dcmp(r[i]-r[j]) <= 0 && dcmp(sqrt(Lsq(c[i]-c[j])) - r[j]+r[i]) <= 0) {
            esc0[i] = true; break;
        }
        if (dcmp(r[i]-r[j]) > 0 && dcmp(sqrt(Lsq(c[i]-c[j])) - r[i]+r[j]) <= 0) esc0[j] = true;
    }
    for (int i=0; i<b; ++i) if (!esc[i]) {
        for (int j=i+1; j<b; ++j) if (p[i] == p[j]) {
            esc[i] = true; break;
        }
        if (esc[i]) continue;
        for (int j=0; j<a; ++j) if (dcmp(sqrt(Lsq(p[i]-c[j])) - r[j]) <= 0) {
            esc[i] = true; break;
        }
    }
    for (int j=a, i=a=0; i<j; ++i) if (!esc0[i]) c[a] = c[i], r[a++] = r[i];
    for (int j=b, i=b=0; i<j; ++i) if (!esc[i]) p[b++] = p[i];
    if (a == 1 && b == 0) return pi2 * r[0];
    if (a == 0 && b < 2) return 0.;
    int s = 0; bool f = a>0;
    for (int i=0; i<a; ++i) if (c[i].y-r[i] < c[s].y-r[s]) s = i;
    for (int i=0; i<b; ++i) {
        if (f) {
            if (p[i].y < c[s].y-r[s]) s = i, f = false;
        } else if (p[i].y < p[s].y) s = i;
    }
    double t = 0., g = 0.; int x = s; bool u = f; Vector v(1.);
    while (true) {
        int y = -1; bool q; long double h;
        if (u) {
            for (int i=0; i<a; ++i) if (i != x) {
                Vector z = c[i] - c[x]; long double l = sqrt(Lsq(z)), sin = (r[i]-r[x])/l, cos = sqrt(1.-sin*sin);
                Vector w(z.x*cos + z.y*sin, z.y*cos - z.x*sin);
                cos = dcmp(Cross(v, w)) < 0 ? -2. - Dot(v, w) / l : Dot(v, w) / l;
                if (y < 0 || dcmp(cos-h) > 0) y = i, h = cos, q = true;
            }
            for (int i=0; i<b; ++i) {
                Vector z = p[i] - c[x]; long double l = sqrt(Lsq(z)), sin = r[x]/l, cos = sqrt(1.-sin*sin);
                Vector w(z.x*cos - z.y*sin, z.y*cos + z.x*sin);
                cos = dcmp(Cross(v, w)) < 0 ? -2. - Dot(v, w) / l : Dot(v, w) / l;
                if (y < 0 || dcmp(cos-h) > 0) y = i, h = cos, q = false;
            }
            h = h < -1. ? pi2-acos(-2.-h) : acos(h);
            if (f && x==s && dcmp(g + h - pi2) >= 0) return t + (pi2-g)*r[s];
            t += h*r[x] + (q ? sqrt(Lsq(c[y] - c[x]) - (r[y]-r[x])*(r[y]-r[x])) : sqrt(Lsq(p[y] - c[x]) - r[x]*r[x]));
            if (!f && !q && y==s) return t;
            g += h; x = y; u = q; v.x = cos(g); v.y = sin(g);
        } else {
            for (int i=0; i<a; ++i) {
                Vector z = c[i] - p[x]; long double l = sqrt(Lsq(z)), sin = r[i]/l, cos = sqrt(1.-sin*sin);
                Vector w(z.x*cos + z.y*sin, z.y*cos - z.x*sin);
                if (dcmp(Cross(v, w)) < 0) continue;
                cos = Dot(v, w) / l;
                if (y < 0 || dcmp(cos-h) > 0) y = i, h = cos, q = true;
            }
            for (int i=0; i<b; ++i) if (i != x) {
                Vector w = p[i] - p[x];
                if (dcmp(Cross(v, w)) < 0) continue;
                long double cos = Dot(v, w) / sqrt(Lsq(w));
                if (y < 0 || dcmp(cos-h) > 0) y = i, h = cos, q = false;
            }
            t += q ? sqrt(Lsq(c[y] - p[x]) - r[y]*r[y]) : sqrt(Lsq(p[y] - p[x]));
            if (!f && !q && y==s) return t;
            g += acos(h); x = y; u = q; v.x = cos(g); v.y = sin(g);
        }
    }
    return t;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(6);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case #" << kase << ": " << solve() << endl;
    return 0;
}