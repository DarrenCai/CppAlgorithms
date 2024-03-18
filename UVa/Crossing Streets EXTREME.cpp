/**
 * UVa11595
 * 过街——极限版
 */

#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;

#define eps 1e-3
struct Point {
    double x, y;
    Point(double x = 0., double y = 0.): x(x), y(y) {}
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

double Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

double Dot(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

double LineInterp(const Point& P, const Vector& v, const Point& Q, const Vector& w) {
    Vector u = P - Q;
    return Cross(w, u) / Cross(v, w);
}

#define M 2.1e9
#define N 42
struct node {
    int h, i;
    bool operator< (const node& rhs) const {
        return h > rhs.h;
    }
};
int g[N*N>>1][N<<1], t[N*N>>1], u[N*N>>1][N], e[N*N>>1], w[N*N>>1], h[N*N>>1], m, n, c, q, kase = 0;
Point p[N*N>>1], s[N]; Vector v[N], d[N*N>>1][N<<1]; double l[N], f[N]; bool vis[N*N>>1][N<<1];

int addPoint(const Point& x) {
    for (int i=0; i<n; ++i) if (p[i] == x) return i;
    p[n] = x;
    return n++;
}

void dfs(int x, int i, int s) {
    vis[x][i] = true;
    if (x == s) u[m][0] = s, e[m] = 1;
    int y = g[x][i];
    if (y != s) {
        u[m][e[m]++] = y;
        double c = 1., f; int z = -1;
        for (int j=0; j<t[y]; ++j)
            if (!vis[y][j] && Cross(d[x][i], d[y][j]) > 0. && (f = Dot(d[x][i], d[y][j])) < c) c = f, z = j;
        if (z >= 0) dfs(y, z, s);
        for (int j=0; j<t[y]; ++j) if (!vis[y][j]) dfs(y, j, y);
    } else u[m][e[m]] = s, w[m++] = 0;
}

int find(const Point& t) {
    for (int i=0, wn; i<m; ++i) {
        for (int j=wn=0; j<e[i]; ++j) {
            int k = dcmp(Cross(p[u[i][j+1]]-p[u[i][j]], t-p[u[i][j]]));
            int d1 = dcmp(p[u[i][j]].y - t.y);
            int d2 = dcmp(p[u[i][j+1]].y - t.y);
            if (k > 0 && d1 <= 0 && d2 > 0) wn++;
            if (k < 0 && d2 <= 0 && d1 > 0) wn--;
        }
        if (wn) return i;
    }
    return m;
}

void addW() {
    Point t; int c; cin >> t.x >> t.y >> c; w[find(t)] += c;
}

int query() {
    Point s, u; cin >> s.x >> s.y >> u.x >> u.y;
    int x = find(s), y = find(u);
    if (x == y) return 0;
    memset(h, 10, sizeof(h)); h[x] = 0;
    priority_queue<node> q; q.push({0, x});
    while (!q.empty()) {
        node z = q.top(); q.pop(); int i = z.i;
        if (i == y) return h[y];
        if (z.h > h[i]) continue;
        for (int j=0; j<t[i]; ++j) {
            int k = g[i][j], v = h[i] + w[i] + w[k] + 1;
            if (h[k] > v) h[k] = v, q.push({h[k], k});
        }
    }
    return h[y];
}

void solve() {
    m = 4;
    while (n--) {
        int a, b, c; cin >> a >> b >> c;
        if (a == 0) {
            if (abs(c) >= M*abs(b)) continue;
            s[m] = {-M, c/(double)-b}; v[m] = {1., 0.}; l[m++] = 2.*M;
        } else if (b == 0) {
            if (abs(c) >= M*abs(a)) continue;
            s[m] = {c/(double)-a, -M}; v[m] = {0., 1.}; l[m++] = 2.*M;
        } else {
            double d = sqrt(a*a + b*b); s[m] = {-M, (a*M-c)/b}; v[m] = {abs(b)/d, b>0 ? -a/d : a/d};
            f[0] = 0.; f[1] = Dot(Point(M, -(a*M+c)/b) - s[m], v[m]); f[2] = Dot(Point((b*M-c)/a, -M) - s[m], v[m]);
            f[3] = Dot(Point(-(b*M+c)/a, M) - s[m], v[m]); sort(f, f+4);
            p[1] = s[m] + v[m]*f[1]; p[2] = s[m] + v[m]*f[2];
            if (!dcmp(f[1]-f[2]) || dcmp(max(max(abs(p[1].x), abs(p[1].y)), max(abs(p[2].x), abs(p[2].y))) - M) > 0)
                continue;
            s[m] = p[1]; l[m++] = f[2] - f[1];
        }
    }
    memset(t, n = 0, sizeof(t));
    for (int i=0; i<m; ++i) {
        f[0] = 0.; f[1] = l[i]; Vector r(-v[i].x, -v[i].y); int c = 2;
        for (int j=0; j<m; ++j) if (dcmp(Cross(v[i], v[j]))) {
            double t = LineInterp(s[i], v[i], s[j], v[j]);
            if (t > 0. && t < l[i]) f[c++] = t;
        }
        sort(f, f+c); c = unique(f, f+c) - f;
        for (int j=1, a = addPoint(s[i]+v[i]*f[0]), b; j<c; a=b, ++j) {
            if (dcmp(f[j]-f[j-1]) == 0) {
                b = a; continue;
            }
            g[a][t[a]] = b = addPoint(s[i]+v[i]*f[j]), g[b][t[b]] = a, d[a][t[a]++] = v[i], d[b][t[b]++] = r;
        }
    }
    memset(vis, 0, sizeof(vis)); dfs(0, 0, m = 0);
    map<pair<int, int>, int> b;
    for (int i=0; i<m; ++i) for (int j=0; j<e[i]; ++j) b[pair<int, int>(u[i][j], u[i][j+1])] = i;
    for (int i=0; i<m; ++i) {
        for (int j=t[i]=0; j<e[i]; ++j) {
            pair<int, int> p(u[i][j+1], u[i][j]);
            if (b.count(p)) g[i][t[i]++] = b[p];
        }
        sort(g[i], g[i]+t[i]); t[i] = unique(g[i], g[i]+t[i]) - g[i];
    }
    while (c--) addW();
    cout << "Case " << ++kase << ':' << endl;
    while (q--) cout << query() << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    s[0] = s[3] = {-M, -M}; s[1] = {M, -M}; s[2] = {-M, M};
    v[0] = v[2] = {1., 0.}; v[1] = v[3] = {0., 1.}; l[0] = l[1] = l[2] = l[3] = 2.*M;
    while (cin >> n >> c >> q && n) solve();
    return 0;
}