/**
 * UVa1438/LA4589
 * 行星
 * NEERC 2009
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define N 62
#define eps 1e-10
struct Point3 {
    double x, y, z;
    Point3(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
    void operator+= (const Point3& A) {
        x += A.x; y += A.y; z += A.z;
    }
    void operator/= (double p) {
        x /= p; y /= p; z /= p;
    }
} p[N], np[N];
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

double Length(const Vector3& A) {
    return sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
}

double Dot(const Vector3& A, const Vector3& B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

Vector3 Cross(const Vector3& A, const Vector3& B) {
    return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
}

struct Face{
    int v[3];
    Vector3 normal(Point3 *P) const {
        return Cross(P[v[1]]-P[v[0]], P[v[2]]-P[v[0]]);
    }
    bool visible(Point3* P, int i) const {
        return Dot(P[i]-P[v[0]], normal(P)) > 0;
    }
} ch[2][N*N];

bool vis[N][N]; int n;

int ConvexHull(Point3* P, int n) {
    ch[0][0] = (Face){0, 1, 2}; ch[0][1] = (Face){2, 1, 0};
    int m = 2; 
    for (int i=3, t, c=1, p=0; i<n; ++i, m=t, c=1^c, p=1^p) {
        for(int j=t=0; j<m; ++j) {
            const Face& f = ch[p][j];
            bool res = f.visible(P, i);
            if (!res) ch[c][t++] = f;
            for (int k=0; k<3; k++) vis[f.v[k]][f.v[(k+1)%3]] = res;
        }
        for (int j=0; j<m; ++j) for (int k=0; k<3; ++k) {
            int a = ch[p][j].v[k], b = ch[p][j].v[(k+1)%3];
            if (!vis[b][a] && vis[a][b]) ch[c][t++] = (Face){a, b, i};
        }
    }
    return m;
}

double calc() {
    int m = ConvexHull(np, n); Point3 c; double v = 0.;
    for (int i=0; i<m; ++i) {
        const int (&r)[3] = ch[~n&1][i].v;
        double s = abs(Dot(p[0] - p[r[0]], Cross(p[r[1]] - p[r[0]], p[r[2]] - p[r[0]])));
        c += (p[0] + p[r[0]] + p[r[1]] + p[r[2]]) * s; v += s;
    }
    c /= 4*v;
    double d = 1e6;
    for (int i=0; i<m; ++i) {
        const int (&r)[3] = ch[~n&1][i].v; Vector3 u = Cross(p[r[1]] - p[r[0]], p[r[2]] - p[r[0]]);
        d = min(d, Dot(p[r[0]] - c, u) / Length(u));
    }
    return d;
}

void add_noise(int i) {
    np[i].x = p[i].x + (rand() / 32767. - .5) * eps;
    np[i].y = p[i].y + (rand() / 32767. - .5) * eps;
    np[i].z = p[i].z + (rand() / 32767. - .5) * eps;
}

void solve() {
    for (int i=0; i<n; ++i) cin >> p[i].x >> p[i].y >> p[i].z, add_noise(i);
    double d = calc(); cin >> n;
    for (int i=0; i<n; ++i) cin >> p[i].x >> p[i].y >> p[i].z, add_noise(i);
    cout << d + calc() << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(5);
    while (cin >> n) solve();
    return 0;
}