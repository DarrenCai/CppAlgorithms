/**
 * UVa1469/LA4973
 * Ardenia王国
 * CERC 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

struct Point3 {
    long long x, y, z;
    Point3(long long x = 0, long long y = 0, long long z = 0): x(x), y(y), z(z) {}
};
typedef Point3 Vector3;

Vector3 operator- (const Vector3& A, const Vector3& B) {
    return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
}

long long Dot(const Vector3& A, const Vector3& B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

Vector3 Cross(const Vector3& A, const Vector3& B) {
    return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
}

struct frac {
    long long p, q;
    frac(long long p, long long q):p(p),q(q) {}
    bool operator< (const frac& rhs) const {
        return p * rhs.q - q * rhs.p < 0;
    }
    void simplify() {
        long long g = __gcd(p, q); p /= g; q /= g;
    }
};

void solve() {
    Point3 a, b, c, d; cin >> a.x >> a.y >> a.z >> b.x >> b.y >> b.z >> c.x >> c.y >> c.z >> d.x >> d.y >> d.z;
    Vector3 u = b-a, v = d-c, n = Cross(u, v);
    frac r(min(min(Dot(c-a, c-a), Dot(c-b, c-b)), min(Dot(d-a, d-a), Dot(d-b, d-b))), 1);
    if (n.x || n.y || n.z) {
        if (Dot(Cross(a-c, v), n) * Dot(Cross(b-c, v), n) <= 0 && Dot(Cross(c-a, u), n) * Dot(Cross(d-a, u), n) <= 0) {
            r.p = Dot(c-a, n); r.p *= r.p; r.q = Dot(n, n); r.simplify();
        } else {
            long long e = Dot(v, v), f = Dot(v, a-c);
            if ((f>=0 && f<=e)) {
                Vector3 w((a.x - c.x)*e - v.x*f, (a.y - c.y)*e - v.y*f, (a.z - c.z)*e - v.z*f);
                frac g(Dot(w, w), e*e); g.simplify(); r = min(r, g);
            }
            f = Dot(v, b-c);
            if ((f>=0 && f<=e)) {
                Vector3 w((b.x - c.x)*e - v.x*f, (b.y - c.y)*e - v.y*f, (b.z - c.z)*e - v.z*f);
                frac g(Dot(w, w), e*e); g.simplify(); r = min(r, g);
            }
            e = Dot(u, u); f = Dot(u, c-a);
            if ((f>=0 && f<=e)) {
                Vector3 w((c.x - a.x)*e - u.x*f, (c.y - a.y)*e - u.y*f, (c.z - a.z)*e - u.z*f);
                frac g(Dot(w, w), e*e); g.simplify(); r = min(r, g);
            }
            f = Dot(u, d-a);
            if ((f>=0 && f<=e)) {
                Vector3 w((d.x - a.x)*e - u.x*f, (d.y - a.y)*e - u.y*f, (d.z - a.z)*e - u.z*f);
                frac g(Dot(w, w), e*e); g.simplify(); r = min(r, g);
            }
        }
    } else {
        long long e = Dot(v, v), f = Dot(v, a-c), g = Dot(v, b-c);
        if ((f>=0 && f<=e) || (g>=0 && g<=e)) {
            Vector3 w((a.x - c.x)*e - v.x*f, (a.y - c.y)*e - v.y*f, (a.z - c.z)*e - v.z*f);
            r.p = Dot(w, w); r.q = e*e; r.simplify();
        } else {
            e = Dot(u, u); f = Dot(u, c-a); g = Dot(u, d-a);
            if ((f>=0 && f<=e) || (g>=0 && g<=e)) {
                Vector3 w((c.x - a.x)*e - u.x*f, (c.y - a.y)*e - u.y*f, (c.z - a.z)*e - u.z*f);
                r.p = Dot(w, w); r.q = e*e; r.simplify();
            }
        }
    }
    cout << r.p << ' ' << r.q << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}