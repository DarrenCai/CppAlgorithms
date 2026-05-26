/**
 * UVa1387/LA3705
 * NEERC 2006
 */

#include <iostream>
#include <iomanip>
#include <queue>
#include <cmath>
using namespace std;

#define eps 1e-9
#define N 32
struct arc_p {
    double x, y; int s, c;
    bool operator== (const arc_p &rhs) const {
        return s == rhs.s && c == rhs.c && abs(x-rhs.x) < eps && abs(y-rhs.y) < eps;
    }
} p[40*N];
struct node {
    double d; int u;
    bool operator< (const node& rhs) const {
        return d > rhs.d;
    }
};
priority_queue<node> q; double d[40*N]; bool f[40*N]; int x_[N], y_[N], x[N], y[N], n, r, t;

struct arc {
    int xc, yc; double x1, y1, x2, y2;
    double len() const {
        return r*acos(min((x1*x2+y1*y2)/r/r, 1.));
    }
};

double dis(double x1, double y1, double x2, double y2) {
    double dx = x1-x2, dy = y1-y2;
    return sqrt(dx*dx+dy*dy);
}

double dot(double x1, double y1, double x2, double y2) {
    return x1*x2 + y1*y2;
}

double cross(double x1, double y1, double x2, double y2) {
    return x1*y2 - x2*y1;
}

int sign(double v) {
    return abs(v) < eps ? 0 : (v < 0 ? -1 : 1);
}

bool point_in_rect(double x, double y, int xa, int ya, int xb, int yb) {
    return x > xa+eps && x < xb-eps && y > ya+eps && y < yb-eps;
}

bool point_on_arc(double x, double y, const arc& a) {
    x -= a.xc; y -= a.yc; double s = sqrt(x*x + y*y);
    return dot(x, y, a.x1, a.y1) > eps && dot(x, y, a.x2, a.y2) > eps && 
        sign(cross(x, y, a.x1, a.y1) / s) * sign(cross(x, y, a.x2, a.y2) / s) < 0;
}

bool seg_intersects_seg(double xs, double ys, double xt, double yt, int xa, int ya, int xb, int yb) {
    double x1 = xt - xs, y1 = yt - ys, x2 = xb - xa, y2 = yb - ya, s1 = sqrt(x1*x1 + y1*y1), s2 = sqrt(x2*x2 + y2*y2);
    return sign(cross(x1, y1, xa - xs, ya - ys) / s1) * sign(cross(x1, y1, xb - xs, yb - ys) / s1) < 0 &&
        sign(cross(x2, y2, xs - xa, ys - ya) / s2) * sign(cross(x2, y2, xt - xa, yt - ya) / s2) < 0;
}

bool seg_intersects_rect(double xs, double ys, double xt, double yt, int xa, int ya, int xb, int yb) {
    return point_in_rect(xs, ys, xa, ya, xb, yb) || point_in_rect(xt, yt, xa, ya, xb, yb) ||
        seg_intersects_seg(xs, ys, xt, yt, xa, ya, xb, yb) || seg_intersects_seg(xs, ys, xt, yt, xa, yb, xb, ya);
}

bool seg_intersects_circle(double xs0, double ys0, double xs1, double ys1, int xc, int yc) {
    if (dis(xs0, ys0, xc, yc) < r-eps || dis(xs1, ys1, xc, yc) < r-eps) return true;
    double x1 = xs1 - xs0, y1 = ys1 - ys0, x2 = xc - xs0, y2 = yc - ys0;
    double s = sqrt(x1*x1 + y1*y1), d = abs(cross(x1, y1, x2, y2)) / s, p = dot(x1, y1, x2, y2) / s;
    return d < r-eps && p > eps && p < s-eps;
}

bool arc_intersects_seg(const arc& a, double xs0, double ys0, double xs1, double ys1) {
    double x1 = xs1 - xs0, y1 = ys1 - ys0, x2 = a.xc - xs0, y2 = a.yc - ys0;
    double s = sqrt(x1*x1 + y1*y1), d = abs(cross(x1, y1, x2, y2)) / s;
    if (d > r-eps) return false;
    double p = dot(x1, y1, x2, y2) / s, q = sqrt(r*r - d*d), t = p - q;
    if (t > eps && t < s-eps && point_on_arc(xs0 + x1*t/s, ys0 + y1*t/s, a)) return true;
    return (t = p + q) > eps && t < s-eps && point_on_arc(xs0 + x1*t/s, ys0 + y1*t/s, a);
}

bool arc_intersects_rect(const arc& a, int xa, int ya, int xb, int yb) {
    double x1 = a.xc + a.x1, y1 = a.yc + a.y1, x2 = a.xc + a.x2, y2 = a.yc + a.y2;
    return point_in_rect(x1, y1, xa, ya, xb, yb) || point_in_rect(x2, y2, xa, ya, xb, yb)
        || arc_intersects_seg(a, xa, ya, xb, yb) || arc_intersects_seg(a, xa, yb, xb, ya);
}

bool arc_intersects_circle(const arc& a, int xc, int yc) {
    double x = xc - a.xc, y = yc - a.yc; double s = sqrt(x*x + y*y);
    if (s > 2*r - eps) return false;
    return dis(xc, yc, a.xc + a.x1, a.yc + a.y1) < r-eps || dis(xc, yc, a.xc + a.x2, a.yc + a.y2) < r-eps ||
        (dot(x, y, a.x1, a.y1) > eps && dot(x, y, a.x2, a.y2) > eps && 
            sign(cross(x, y, a.x1, a.y1) / s) * sign(cross(x, y, a.x2, a.y2) / s) < 0);
}

bool seg_intersects_skyscraper(double xs0, double ys0, double xs1, double ys1, int i) {
    return seg_intersects_rect(xs0, ys0, xs1, ys1, x_[i]-r, y_[i], x[i]+r, y[i]) || 
           seg_intersects_rect(xs0, ys0, xs1, ys1, x_[i], y_[i]-r, x[i], y[i]+r) ||
           seg_intersects_circle(xs0, ys0, xs1, ys1, x_[i], y_[i]) ||
           seg_intersects_circle(xs0, ys0, xs1, ys1, x_[i], y[i]) ||
           seg_intersects_circle(xs0, ys0, xs1, ys1, x[i], y_[i]) ||
           seg_intersects_circle(xs0, ys0, xs1, ys1, x[i], y[i]);
}

bool arc_intersects_skyscraper(const arc & a, int i) {
    return arc_intersects_rect(a, x_[i]-r, y_[i], x[i]+r, y[i]) || 
           arc_intersects_rect(a, x_[i], y_[i]-r, x[i], y[i]+r) ||
           arc_intersects_circle(a, x_[i], y_[i]) ||
           arc_intersects_circle(a, x_[i], y[i]) ||
           arc_intersects_circle(a, x[i], y_[i]) ||
           arc_intersects_circle(a, x[i], y[i]);
}

bool direct_fly(double x0, double y0, double x1, double y1) {
    for (int i=1; i<=n; ++i) if (seg_intersects_skyscraper(x0, y0, x1, y1, i))
        return false;
    return true;
}

bool arc_fly(int s, const arc& a) {
    for (int i=1; i<=n; ++i) if (i != s && arc_intersects_skyscraper(a, i))
        return false;
    return true;
}

bool valid(double x, double y, double xl, double yl) {
    double p = dot(x, y, xl, yl);
    return p > eps && cross(x, y, xl, yl) < p+eps;
}

int get_idx(const arc_p& a) {
    for (int i=2; i<=t; ++i) if (p[i] == a) return i;
    d[++t] = 1e99; p[t] = a; f[t] = false;
    return t;
}

void update(const arc_p& a, double dd) {
    for (int u=2; u<=t; ++u) if (p[u] == a) {
        if (dd < d[u]) q.push({d[u] = dd, u});
        return;
    }
    p[++t] = a; f[t] = false; q.push({d[t] = dd, t});
}

void solve_src_tangent_rc(double xs, double ys, int s, int c) {
    int xc, yc, dx, dy;
    if (c == 0) xc = x_[s], yc = y_[s], dx = -1, dy = -1;
    else if (c == 1) xc = x[s], yc = y_[s], dx = 1, dy = -1;
    else if (c == 2) xc = x[s], yc = y[s], dx = 1, dy = 1;
    else xc = x_[s], yc = y[s], dx = -1, dy = 1;
    double vx = xs - xc, vy = ys - yc, m = sqrt(vx*vx + vy*vy);
    if (m < r-eps) return;
    if (m < r+eps) {
        if (valid(vx, vy, dx, dy)) update({xs, ys, s, c}, 0);
        return;
    }
    double k1 = r*r/m/m, k2 = r*sqrt(m*m - r*r)/m/m, x = k1*vx - k2*vy, y = k1*vy + k2*vx;
    if (valid(x, y, dx, dy) && direct_fly(xs, ys, x+xc, y+yc)) update({x+xc, y+yc, s, c}, dis(xs, ys, x+xc, y+yc));
    x = k1*vx + k2*vy; y = k1*vy - k2*vx;
    if (valid(x, y, dx, dy) && direct_fly(xs, ys, x+xc, y+yc)) update({x+xc, y+yc, s, c}, dis(xs, ys, x+xc, y+yc));
}

void solve_dst_tangent_arc(double xt, double yt, int u) {
    int xc, yc, dx, dy;
    if (p[u].c == 0) xc = x_[p[u].s], yc = y_[p[u].s], dx = -1, dy = -1;
    else if (p[u].c == 1) xc = x[p[u].s], yc = y_[p[u].s], dx = 1, dy = -1;
    else if (p[u].c == 2) xc = x[p[u].s], yc = y[p[u].s], dx = 1, dy = 1;
    else xc = x_[p[u].s], yc = y[p[u].s], dx = -1, dy = 1;
    double vx = xt - xc, vy = yt - yc, m = sqrt(vx*vx + vy*vy);
    if (m < r-eps) return;
    if (m < r+eps) {
        arc a = {xc, yc, p[u].x - xc, p[u].y - yc, vx, vy}; double d1 = d[u] + a.len();
        if (valid(vx, vy, dx, dy) && arc_fly(p[u].s, a) && d1 < d[1]) q.push({d[1] = d1, 1});
        return;
    }
    double k1 = r*r/m/m, k2 = r*sqrt(m*m - r*r)/m/m;
    arc a = {xc, yc, k1*vx - k2*vy, k1*vy + k2*vx, p[u].x - xc, p[u].y - yc};
    if (valid(a.x1, a.y1, dx, dy) && arc_fly(p[u].s, a)) {
        double d1 = d[u] + a.len() + dis(xt, yt, a.x1 + xc, a.y1 + yc);
        if (d1 < d[1] && direct_fly(xt, yt, a.x1 + xc, a.y1 + yc)) q.push({d[1] = d1, 1});
    }
    a.x1 = k1*vx + k2*vy; a.y1 = k1*vy - k2*vx;
    if (valid(a.x1, a.y1, dx, dy) && arc_fly(p[u].s, a)) {
        double d1 = d[u] + a.len() + dis(xt, yt, a.x1 + xc, a.y1 + yc);
        if (d1 < d[1] && direct_fly(xt, yt, a.x1 + xc, a.y1 + yc)) q.push({d[1] = d1, 1});
    }
}

void solve_arc_tangent_rc(int u, int s, int c) {
    int x1, y1, dx1, dy1, x2, y2, dx2, dy2;
    if (p[u].c == 0) x1 = x_[p[u].s], y1 = y_[p[u].s], dx1 = -1, dy1 = -1;
    else if (p[u].c == 1) x1 = x[p[u].s], y1 = y_[p[u].s], dx1 = 1, dy1 = -1;
    else if (p[u].c == 2) x1 = x[p[u].s], y1 = y[p[u].s], dx1 = 1, dy1 = 1;
    else x1 = x_[p[u].s], y1 = y[p[u].s], dx1 = -1, dy1 = 1;
    if (c == 0) x2 = x_[s], y2 = y_[s], dx2 = -1, dy2 = -1;
    else if (c == 1) x2 = x[s], y2 = y_[s], dx2 = 1, dy2 = -1;
    else if (c == 2) x2 = x[s], y2 = y[s], dx2 = 1, dy2 = 1;
    else x2 = x_[s], y2 = y[s], dx2 = -1, dy2 = 1;
    double vx = .5 * (x2 - x1), vy = .5 * (y2 - y1), m = sqrt(vx*vx + vy*vy);
    arc a = {x1, y1, p[u].x - x1, p[u].y - y1, -vy*r/m, vx*r/m};
    if (valid(a.x2, a.y2, dx1, dy1) && valid(a.x2, a.y2, dx2, dy2) && arc_fly(p[u].s, a) &&
        direct_fly(a.x2 + x1, a.y2 + y1, a.x2 + x2, a.y2 + y2))
        update({a.x2 + x2, a.y2 + y2, s, c}, d[u] + a.len() + dis(a.x2 + x1, a.y2 + y1, a.x2 + x2, a.y2 + y2));
    if (valid(a.x2 *= -1, a.y2 *= -1, dx1, dy1) && valid(a.x2, a.y2, dx2, dy2) && arc_fly(p[u].s, a) &&
        direct_fly(a.x2 + x1, a.y2 + y1, a.x2 + x2, a.y2 + y2))
        update({a.x2 + x2, a.y2 + y2, s, c}, d[u] + a.len() + dis(a.x2 + x1, a.y2 + y1, a.x2 + x2, a.y2 + y2));
    if (m < r-eps) return;
    if (m < r+eps) {
        a.x2 = vx; a.y2 = vy;
        if (valid(a.x2, a.y2, dx1, dy1) && arc_fly(p[u].s, a)) update({a.x2 + x2, a.y2 + y2, s, c}, d[u] + a.len());
        return;
    }
    double k1 = r*r/m/m, k2 = r*sqrt(m*m - r*r)/m/m;
    a.x2 = k1*vx - k2*vy; a.y2 = k1*vy + k2*vx;
    if (valid(a.x2, a.y2, dx1, dy1) && valid(-a.x2, -a.y2, dx2, dy2) && arc_fly(p[u].s, a) &&
        direct_fly(a.x2 + x1, a.y2 + y1, x2 - a.x2, y2 - a.y2))
        update({x2 - a.x2, y2 - a.y2, s, c}, d[u] + a.len() + dis(a.x2 + x1, a.y2 + y1, x2 - a.x2, y2 - a.y2));
    a.x2 = k1*vx + k2*vy; a.y2 = k1*vy - k2*vx;
    if (valid(a.x2, a.y2, dx1, dy1) && valid(-a.x2, -a.y2, dx2, dy2) && arc_fly(p[u].s, a) &&
        direct_fly(a.x2 + x1, a.y2 + y1, x2 - a.x2, y2 - a.y2))
        update({x2 - a.x2, y2 - a.y2, s, c}, d[u] + a.len() + dis(a.x2 + x1, a.y2 + y1, x2 - a.x2, y2 - a.y2));
}

void solve_arc_trans(int u) {
    arc a; double x1, y1, x2, y2;
    if (p[u].c == 0) {
        a.xc = x_[p[u].s]; a.yc = y_[p[u].s]; a.x1 = p[u].x - a.xc; a.y1 = p[u].y - a.yc; a.x2 = 0; a.y2 = -r;
        if (arc_fly(p[u].s, a) && direct_fly(x1 = a.xc, y1 = a.yc-r, x2 = x[p[u].s], y2 = a.yc-r))
            update({x2, y2, p[u].s, 1}, d[u] + a.len() + x2 - x1);
        a.x2 = -r; a.y2 = 0;
        if (arc_fly(p[u].s, a) && direct_fly(x1 = a.xc-r, y1 = a.yc, x2 = a.xc-r, y2 = y[p[u].s]))
            update({x2, y2, p[u].s, 3}, d[u] + a.len() + y2 - y1);
    } else if (p[u].c == 1) {
        a.xc = x[p[u].s]; a.yc = y_[p[u].s]; a.x1 = p[u].x - a.xc; a.y1 = p[u].y - a.yc; a.x2 = r; a.y2 = 0;
        if (arc_fly(p[u].s, a) && direct_fly(x1 = a.xc+r, y1 = a.yc, x2 = a.xc+r, y2 = y[p[u].s]))
            update({x2, y2, p[u].s, 2}, d[u] + a.len() + y2 - y1);
        a.x2 = 0; a.y2 = -r;
        if (arc_fly(p[u].s, a) && direct_fly(x1 = x_[p[u].s], y1 = a.yc-r, x2 = a.xc, y2 = a.yc-r))
            update({x1, y1, p[u].s, 0}, d[u] + a.len() + x2 - x1);
    } else if (p[u].c == 2) {
        a.xc = x[p[u].s]; a.yc = y[p[u].s]; a.x1 = p[u].x - a.xc; a.y1 = p[u].y - a.yc; a.x2 = 0; a.y2 = r;
        if (arc_fly(p[u].s, a) && direct_fly(x1 = x_[p[u].s], y1 = a.yc+r, x2 = a.xc, y2 = a.yc+r))
            update({x1, y1, p[u].s, 3}, d[u] + a.len() + x2 - x1);
        a.x2 = r; a.y2 = 0;
        if (arc_fly(p[u].s, a) && direct_fly(x1 = a.xc+r, y1 = y_[p[u].s], x2 = a.xc+r, y2 = a.yc))
            update({x1, y1, p[u].s, 1}, d[u] + a.len() + y2 - y1);
    } else {
        a.xc = x_[p[u].s]; a.yc = y[p[u].s]; a.x1 = p[u].x - a.xc; a.y1 = p[u].y - a.yc; a.x2 = -r; a.y2 = 0;
        if (arc_fly(p[u].s, a) && direct_fly(x1 = a.xc-r, y1 = y_[p[u].s], x2 = a.xc-r, y2 = a.yc))
            update({x1, y1, p[u].s, 0}, d[u] + a.len() + y2 - y1);
        a.x2 = 0; a.y2 = r;
        if (arc_fly(p[u].s, a) && direct_fly(x1 = a.xc, y1 = a.yc+r, x2 = x[p[u].s], y2 = a.yc+r))
            update({x2, y2, p[u].s, 2}, d[u] + a.len() + x2 - x1);
    }
}

void solve() {
    cin >> x_[0] >> y_[0] >> x[0] >> y[0];
    for (int i=1; i<=n; ++i) cin >> x_[i] >> y_[i] >> x[i] >> y[i];
    if (direct_fly(x_[0], y_[0], x[0], y[0])) {
        cout << dis(x_[0], y_[0], x[0], y[0]) << endl;
        return;
    }
    priority_queue<node> ept; d[1] = 1e99; f[t = 1] = false; q.swap(ept);
    for (int i=1; i<=n; ++i) for (int j=0; j<4; ++j) solve_src_tangent_rc(x_[0], y_[0], i, j);
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (u == 1) {
            cout << d[1] << endl;
            return;
        }
        if (f[u]) continue;
        f[u] = true;
        solve_dst_tangent_arc(x[0], y[0], u);
        for (int i=1; i<=n; ++i) if (i != p[u].s) for (int j=0; j<4; ++j) solve_arc_tangent_rc(u, i, j);
        solve_arc_trans(u);
    }
    cout << "no solution" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    while (cin >> r >> n) solve();
    return 0;
}