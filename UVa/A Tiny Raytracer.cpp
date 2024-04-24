/**
 * UVa12313
 * 微型光线追踪器
 */

#include <iostream>
#include <cmath>
using namespace std;
struct Point3 {
    double x, y, z;
    Point3(double x = 0., double y = 0., double z = 0.): x(x), y(y), z(z) {}
    void Normalize() {
        double l = sqrt(x*x + y*y + z*z); x /= l; y /= l; z /= l;
    }
};
typedef Point3 Vector3;

Vector3 operator+ (const Vector3& A, const Vector3& B) {
    return Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
}

Vector3 operator- (const Vector3& A, const Vector3& B) {
    return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
}

Vector3 operator* (const Vector3& A, double p) {
    return Vector3(A.x * p, A.y * p, A.z * p);
}

double Dot(const Vector3& A, const Vector3& B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

Vector3 Cross(const Vector3& A, const Vector3& B) {
    return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
}

#define eps 1e-10
#define M 202
#define N 22
#define P 26
#define T 52
#define X 4
struct {Point3 v[P], n[T], c; int f[T][3], p, t; double l, r, m;} obj[N];
struct Ray {
    Point3 p; Vector3 v; double m;
    Ray(const Point3& p, const Vector3 v, double m): p(p), v(v), m(m) {this->v.Normalize();}
};
struct Ints {Point3 p; int i, j; Ints():i(-1){}};
Point3 img[M][M], p, t, g, c; Vector3 up; double a, f; int w, h, n, q;

Ints get_ints(const Point3& p, const Vector3& v) {
    double t = -1.; Ints it;
    for (int i=0; i<n; ++i) for (int j=0; j<obj[i].t; ++j) {
        if (abs(Dot(v, obj[i].n[j])) < eps) continue;
        const Point3 &a = obj[i].v[obj[i].f[j][0]], &b = obj[i].v[obj[i].f[j][1]], &c = obj[i].v[obj[i].f[j][2]];
        const Vector3 &n = obj[i].n[j]; double q = Dot(n, a-p) / Dot(n, v);
        if (q < eps || (t>eps && q>=t)) continue;
        Point3 r = p + v*q; Vector3 c1 = Cross(b-a, r-a), c2 = Cross(c-b, r-b), c3 = Cross(a-c, r-c);
        if (Dot(c1, c2)>0. && Dot(c1, c3)>eps) t = q, it.p = r, it.i = i, it.j = j;
    }
    return it;
}

double shade(const Point3& p, const Vector3& norm) {
    Vector3 v = g-p; double l = sqrt(v.x*v.x + v.y*v.y + v.z*v.z); v.x /= l; v.y /= l; v.z /= l;
    for (int i=0; i<n; ++i) for (int j=0; j<obj[i].t; ++j) {
        if (abs(Dot(v, obj[i].n[j])) < eps) continue;
        const Point3 &a = obj[i].v[obj[i].f[j][0]], &b = obj[i].v[obj[i].f[j][1]], &c = obj[i].v[obj[i].f[j][2]];
        const Vector3 &n = obj[i].n[j]; double q = Dot(n, a-p) / Dot(n, v);
        if (q < eps || q > l-eps) continue;
        Point3 r = p + v*q; Vector3 c1 = Cross(b-a, r-a), c2 = Cross(c-b, r-b), c3 = Cross(a-c, r-c);
        if (Dot(c1, c2)>eps && Dot(c1, c3)>eps) return 0.;
    }
    return abs(Dot(v, norm));
}

Vector3 get_point_color(const Point3& p, const Vector3& v, const Vector3& oc) {
    return Vector3(oc.x*c.x, oc.y*c.y, oc.z*c.z) * (a + (1.-a)*shade(p, v));
}

bool tir(const Vector3& v, const Vector3& n, double m, double q) {
    double c = Dot(v, n);
    return m*sqrt(1.-c*c) >= q*(1.-eps);
}

Vector3 fl_vec(const Vector3& v, const Vector3& n) {
    return v - n * (2.*Dot(v, n));
}

Vector3 fr_vec(const Vector3& v, const Vector3& n, double m,  double q) {
    double c = Dot(v, n), s = m*sqrt(1.-c*c)/q; Vector3 n1 = n*c, t = v-n1; n1.Normalize(); t.Normalize();
    return n1 * sqrt(1.-s*s) + t * s;
}

Vector3 trace_ray(int d, const Ray& ray) {
    Vector3 c, l, r; Ints it = get_ints(ray.p, ray.v);
    if (it.i >= 0) {
        double fl = obj[it.i].l, fr = obj[it.i].r, m = ray.m==1. ? obj[it.i].m : 1.;
        c = get_point_color(it.p, obj[it.i].n[it.j], obj[it.i].c) * (1. - fl - fr);
        if (d == X) return c;
        if (tir(ray.v, obj[it.i].n[it.j], ray.m, obj[it.i].m)) fr = 0.;
        if (fl > 0.) l = trace_ray(d+1, Ray(it.p, fl_vec(ray.v, obj[it.i].n[it.j]), ray.m)) * fl;
        if (fr > 0.) r = trace_ray(d+1, Ray(it.p, fr_vec(ray.v, obj[it.i].n[it.j], ray.m, m), m)) * fr;
    }
    return c + l + r;
}

void print(double c) {
    int v = int(c*255.+.5), a = v>>4, b = v&15;
    a < 10 ? cout << a : cout << char('a'+a-10); b < 10 ? cout << b : cout << char('a'+b-10);
}

void print(const Vector3& c) {
    print(c.x); print(c.y); print(c.z); cout << ' ';
}

void solve() {
    for (int i=0; i<n; ++i) {
        cin >> obj[i].p;
        for (int j=0; j<obj[i].p; ++j) cin >> obj[i].v[j].x >> obj[i].v[j].y >> obj[i].v[j].z;
        cin >> obj[i].t;
        for (int j=0; j<obj[i].t; ++j) {
            cin >> obj[i].f[j][0] >> obj[i].f[j][1] >> obj[i].f[j][2];
            const Point3 &a = obj[i].v[obj[i].f[j][0]], &b = obj[i].v[obj[i].f[j][1]], &c = obj[i].v[obj[i].f[j][2]];
            Vector3& v = obj[i].n[j] = Cross(b-a, c-a); v.Normalize();
        }
        cin >> obj[i].c.x >> obj[i].c.y >> obj[i].c.z >> obj[i].l >> obj[i].r >> obj[i].m;
    }
    cin >> g.x >> g.y >> g.z >> a >> c.x >> c.y >> c.z >> q;
    while (q--) {
        cin >> p.x >> p.y >> p.z >> t.x >> t.y >> t.z >> up.x >> up.y >> up.z >> f >> w >> h;
        Vector3 z = t-p; z.Normalize(); Vector3 x = Cross(z, up);
        double d = tan(f*M_PI/360.)/w, xi = d*(1-w), y0 = d*(h-1); d *= 2.;
        for (int i=0; i<w; ++i, xi+=d) {
            double yi = y0;
            for (int j=0; j<h; ++j, yi-=d) img[i][j] = trace_ray(0, Ray(p, x*xi + up*yi + z, 1.));
        }
        cout << w << ' ' << h << endl;
        for (int i=0; i<h; ++i) {
            for (int j=0; j<w; ++j) print(img[j][i]);
            cout << endl;
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}