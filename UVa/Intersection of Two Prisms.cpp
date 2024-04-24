/**
 * UVa1483/LA5075
 * Tokyo 2010
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define eps 1e-10
#define N 105
int x1[N], y1[N], x2[N], z2[N]; int m, n, t, e;
struct Point3 {
    double x, y, z;
    Point3(double x = 0., double y = 0., double z = 0.): x(x), y(y), z(z) {}
} p[N], s[N<<1], q[N<<1], f[N];
typedef Point3 Vector3;

Vector3 operator+ (const Vector3& A, const Vector3& B) {
    return Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
}

Vector3 operator- (const Vector3& A, const Vector3& B) {
    return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
}

int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0. ? -1 : 1);
}

bool operator== (const Point3& a, const Point3& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0 && dcmp(a.z - b.z) == 0;
}

double Dot(const Vector3& A, const Vector3& B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

Vector3 Cross(const Vector3& A, const Vector3& B) {
    return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
}

Vector3 Area2(const Point3* p, int n) {
    Vector3 s;
    for (int i=n-2; i>0; --i) s = s + Cross(p[i]-p[0], p[i+1]-p[0]);
    return s;
}

double interp(int x1, int y1, int x2, int y2, double x) {
    return ((x-x1)*y2 + (x2-x)*y1) / (x2-x1);
}

bool find(const Point3& p) {
    for (int i=0; i<e; ++i) if (f[i] == p) return true;
    return false;
}

double solve() {
    for (int i=0; i<m; ++i) cin >> x1[i] >> y1[i];
    for (int i=0; i<n; ++i) cin >> x2[i] >> z2[i];
    x1[m] = x1[0]; y1[m] = y1[0]; x2[n] = x2[0]; z2[n] = z2[0];
    for (int i=t=e=0; i<m; ++i) {
        int a = min(x1[i], x1[i+1]), b = max(x1[i], x1[i+1]), c = 0;
        if (a == b) {
            for (int j=0; j<n; ++j) {
                int l = min(x2[j], x2[j+1]), r = max(x2[j], x2[j+1]);
                if (a < l || a > r) continue;
                if (a == x2[j]) p[c].x = a, p[c].y = y1[i], p[c++].z = z2[j];
                else if (a != x2[j+1])
                    p[c].x = a, p[c].y = y1[i], p[c++].z = interp(x2[j], z2[j], x2[j+1], z2[j+1], a);
            }
            if (c == 2) {
                p[2].x = p[3].x = a; p[2].y = p[3].y = y1[i+1]; p[2].z = p[1].z; p[3].z = p[0].z; c = 4;
                f[e].x = a; f[e].y = (y1[i] + y1[i+1]) / 2.; f[e++].z = (p[0].z + p[1].z) / 2.;
            }
        } else for (int j=0; j<n; ++j) {
            int l = min(max(x2[j], a), max(x2[j+1], a)), r = max(min(x2[j], b), min(x2[j+1], b));
            if (l == r) {
                if (x2[j] == l) p[c].x = x2[j], p[c].z = z2[j],
                    p[c++].y = interp(x1[i], y1[i], x1[i+1], y1[i+1], x2[j]);
            } else if (l < r) {
                if (x2[j] > x2[j+1]) r = l+r, l = r-l, r = r-l;
                if (x2[j+1] != l) p[c].x = l, p[c].y = interp(x1[i], y1[i], x1[i+1], y1[i+1], l),
                    p[c++].z = interp(x2[j], z2[j], x2[j+1], z2[j+1], l);
                if (x2[j+1] != r) p[c].x = r, p[c].y = interp(x1[i], y1[i], x1[i+1], y1[i+1], r),
                    p[c++].z = interp(x2[j], z2[j], x2[j+1], z2[j+1], r);
            }
        }
        if (c > 2) s[t] = Area2(p, c), q[t++] = p[0];
    }
    for (int i=0; i<n; ++i) {
        int a = min(x2[i], x2[i+1]), b = max(x2[i], x2[i+1]), c = 0;
        if (a == b) {
            for (int j=0; j<m; ++j) {
                int l = min(x1[j], x1[j+1]), r = max(x1[j], x1[j+1]);
                if (a < l || a > r) continue;
                if (a == x1[j]) p[c].x = a, p[c].y = y1[j], p[c++].z = z2[i];
                else if (a != x1[j+1])
                    p[c].x = a, p[c].y = interp(x1[j], y1[j], x1[j+1], y1[j+1], a), p[c++].z = z2[i];
            }
            if (c == 2) {
                if (find(Point3(a, (p[0].y + p[1].y) / 2., (z2[i] + z2[i+1]) / 2.))) continue;
                p[2].x = p[3].x = a; p[2].y = p[1].y; p[2].z = p[3].z = z2[i+1]; p[3].y = p[0].y; c = 4;
            }
        } else for (int j=0; j<m; ++j) {
            int l = min(max(x1[j], a), max(x1[j+1], a)), r = max(min(x1[j], b), min(x1[j+1], b));
            if (l == r) {
                if (x1[j] == l) p[c].x = x1[j], p[c].y = y1[j],
                    p[c++].z = interp(x2[i], z2[i], x2[i+1], z2[i+1], x1[j]);
            } else if (l < r) {
                if (x1[j] > x1[j+1]) r = l+r, l = r-l, r = r-l;
                if (x1[j+1] != l) p[c].x = l, p[c].y = interp(x1[j], y1[j], x1[j+1], y1[j+1], l),
                    p[c++].z = interp(x2[i], z2[i], x2[i+1], z2[i+1], l);
                if (x1[j+1] != r) p[c].x = r, p[c].y = interp(x1[j], y1[j], x1[j+1], y1[j+1], r),
                    p[c++].z = interp(x2[i], z2[i], x2[i+1], z2[i+1], r);
            }
        }
        if (c > 2) s[t] = Area2(p, c), q[t++] = p[0];
    }
    double ans = 0.;
    for (int i=1; i<t; ++i) ans += abs(Dot(s[i], q[i]-q[0]));
    return ans / 6.;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(4);
    while (cin >> m >> n && m) cout << solve() << endl;
    return 0;
}