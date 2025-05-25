/**
 * UVa11921
 * 拯救公主
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
using namespace std;

#define N 52
#define eps 1e-9

struct point {
    double x, y;
    bool operator< (const point& p) const {
        if (abs(x-p.x) < eps && abs(y-p.y) < eps) return false;
        return x < p.x || (x == p.x && y < p.y);
    }
} p[N*N<<2];

struct node {
    double d; int u;
    bool operator< (const node& rhs) const {
        return d > rhs.d;
    }
};

int x[N], y[N], r[N], a[N][N<<2], b[N<<2], c[N], xp, yp, xt, yt, n, t;
struct edge {int v; double w;}; vector<edge> g[N*N<<2]; map<point, int> id;
double e1 = 1+eps, e2 = e1*e1, d[N*N<<2]; bool e[N*N<<2], f[N*N<<2];

int add_point(double x, double y) {
    point a = {x, y};
    if (id.count(a)) return id[a];
    g[t].clear(); p[t] = a; e[t] = f[t] = false;
    return id[a] = t++;
}

bool s_i_c(double xa, double ya, double xb, double yb, int i) {
    double dx = xb-xa, dy = yb-ya, d = dx*dx+dy*dy, vx = x[i]-xa, vy = y[i]-ya, s = vx*dy -vy*dx, e = vx*dx + vy*dy;
    return s*s < d*r[i]*r[i]*e2 && e > -eps*d && e < e1*d;
}

void add_edge(int i, double xi, double yi, int j, double xj, double yj, double w) {
    int u = add_point(xi, yi);
    if (i >= 0 && u+1 == t) a[i][c[i]++] = u;
    int v = add_point(xj, yj); g[u].push_back({v, w}); g[v].push_back({u, w});
    if (j >= 0 && v+1 == t) a[j][c[j]++] = v;
}

void p_t_c(int xp, int yp, int i) {
    double dx = x[i]-xp, dy = y[i]-yp, d2 = dx*dx + dy*dy, d = sqrt(d2), d1 = ((d2-2*r[i]*r[i])/d + d)/2;
    double x0 = xp + dx*d1/d, y0 = yp + dy*d1/d, e = sqrt(d2-r[i]*r[i] - d1*d1) / d; dx *= e; dy *= e;
    double x1 = x0 - dy, y1 = y0 + dx, w = sqrt(d2-r[i]*r[i]); bool ok = true;
    for (int j=0; j<n; ++j) if (j!=i && s_i_c(xp, yp, x1, y1, j)) {ok = false; break;}
    if (ok) add_edge(-1, xp, yp, i, x1, y1, w);
    x1 = x0 + dy; y1 = y0 - dx; ok = true;
    for (int j=0; j<n; ++j) if (j!=i && s_i_c(xp, yp, x1, y1, j)) {ok = false; break;}
    if (ok) add_edge(-1, xp, yp, i, x1, y1, w);
}

void c_t_c(int i, int j) {
    int dx = x[j]-x[i], dy = y[j]-y[i], d2 = dx*dx+dy*dy;
    double d = r[i]-r[j], ei = r[i]*d/d2, ej = r[j]*d/d2, w = sqrt(d2 - d*d);
    double xi = x[i] + ei*dx, yi = y[i] + ei*dy, xj = x[j] + ej*dx, yj = y[j] + ej*dy;
    ei = sqrt(r[i]*r[i]/double(d2) - ei*ei); ej = sqrt(r[j]*r[j]/double(d2) - ej*ej);
    double x1 = xi - ei*dy, y1 = yi + ei*dx, x2 = xj - ej*dy, y2 = yj + ej*dx; bool ok = true;
    for (int k=0; k<n; ++k) if (k!=i && k!=j && s_i_c(x1, y1, x2, y2, k)) {ok = false; break;}
    if (ok) add_edge(i, x1, y1, j, x2, y2, w);
    x1 = xi + ei*dy; y1 = yi - ei*dx; x2 = xj + ej*dy; y2 = yj - ej*dx; ok = true;
    for (int k=0; k<n; ++k) if (k!=i && k!=j && s_i_c(x1, y1, x2, y2, k)) {ok = false; break;}
    if (ok) add_edge(i, x1, y1, j, x2, y2, w);
    if (d2 == (r[i]+r[j])*(r[i]+r[j])) {
        double e = r[i]/sqrt(d2), x1 = x[i] + e*dx, y1 = y[i] + e*dy; int u = add_point(x1, y1); ::e[u] = true;
        if (u+1 == t) a[i][c[i]++] = u, a[j][c[j]++] = u;
        return;
    }
    d = r[i]+r[j]; ei = r[i]*d/d2; ej = -r[j]*d/d2; w = sqrt(d2 - d*d);
    xi = x[i] + ei*dx; yi = y[i] + ei*dy; xj = x[j] + ej*dx; yj = y[j] + ej*dy;
    ei = sqrt(r[i]*r[i]/double(d2) - ei*ei); ej = sqrt(r[j]*r[j]/double(d2) - ej*ej);
    x1 = xi - ei*dy; y1 = yi + ei*dx; x2 = xj + ej*dy; y2 = yj - ej*dx; ok = true;
    for (int k=0; k<n; ++k) if (k!=i && k!=j && s_i_c(x1, y1, x2, y2, k)) {ok = false; break;}
    if (ok) add_edge(i, x1, y1, j, x2, y2, w);
    x1 = xi + ei*dy; y1 = yi - ei*dx; x2 = xj - ej*dy; y2 = yj + ej*dx; ok = true;
    for (int k=0; k<n; ++k) if (k!=i && k!=j && s_i_c(x1, y1, x2, y2, k)) {ok = false; break;}
    if (ok) add_edge(i, x1, y1, j, x2, y2, w);
}

bool cmp(int i, int j) {
    return d[i] < d[j];
}

double solve() {
    cin >> xp >> yp >> xt >> yt >> n;
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i] >> r[i], c[i] = 0;
    id.clear(); t = 0; add_point(xp, yp); add_point(xt, yt);
    int dx = xt-xp, dy = yt-yp, d2 = dx*dx+dy*dy; bool ok = true;
    for (int i=0; i<n; ++i) if (s_i_c(xp, yp, xt, yt, i)) {
        ok = false; break;
    }
    if (ok) return sqrt(d2);
    for (int i=0; i<n; ++i) {
        p_t_c(xp, yp, i); p_t_c(xt, yt, i);
        for (int j=i+1; j<n; ++j) c_t_c(i, j);
        if (c[i] < 2) continue;
        for (int j=0; j<c[i]; ++j) b[j] = j, d[j] = atan2(p[a[i][j]].y - y[i], p[a[i][j]].x - x[i]);
        sort(b, b+c[i], cmp);
        for (int j=0; j<c[i]; ++j) {
            double w = j ? d[b[j]] - d[b[j-1]] : d[b[0]] + M_PI + M_PI - d[b[c[i]-1]];
            int u = a[i][b[j]], v = a[i][b[j ? j-1 : c[i]-1]];
            w = w*r[i]; g[u].push_back({v, w}); g[v].push_back({u, w});
        }
    }
    for (int i=0; i<t; ++i) d[i] = 1e30;
    priority_queue<node> q; q.push({d[0]=0., 0});
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (u == 1) return d[1];
        if (e[u] || f[u]) continue;
        f[u] = true;
        for (int i=g[u].size()-1; i>=0; --i) {
            int v = g[u][i].v; double d1 = d[u] + g[u][i].w;
            if (d[v] > d1) q.push({d[v] = d1, v});
        }
    }
    return d[1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(8);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case " << kase << ": " << solve() << endl;
    return 0;
}