/**
 * UVa12214/LA4500
 * 交通堵塞
 * Dhaka 2009
 * https://blog.csdn.net/CY05627/article/details/93601315
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define N 2200
#define eps 1e-6

struct point {
    double x, y;
    point operator- (const point& t) const {
        point r; r.x = x - t.x; r.y = y-t.y;
        return r;
    }
    point operator+ (const point& t) const {
        point r; r.x = x + t.x; r.y = y + t.y;
        return r;
    }
    point operator* (double s) const {
        point r; r.x = x * s; r.y = y * s;
        return r;
    }
    point norm() const {
        point t; t.x = -y; t.y = x;
        return t;
    }
    point rotate(double a) {
        point t; double c = cos(a), s = sin(a); t.x = x*c - y*s; t.y = x*s + y*c;
        return t;
    }
    double cross(const point& t) const {
        return x*t.y - y*t.x;
    }
    double dot(const point& t) const {
        return x*t.x + y*t.y;
    }
    double len() const {
        return sqrt(x*x + y*y);
    }
} p[N];

double scale(const point& a, const point& b, const point& c, const point& d) {
	point t1 = b - a, t2 = c - b;
	return d.cross(t1) / t2.cross(d);
}

bool between(const point& x, const point& a, const point& b) {
    point v1 = x-a, v2 = x-b; double c = v1.cross(v2), d = v1.dot(v2);
    return c>-eps && c<eps && d<eps;
}

double fuel[N][N], d[N], f;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int kase = 0, n;
    cout << fixed << setprecision(3);
    while (cin>>n>>f && n) {
        double theta = asin(1/f); int t = 0;
        for (int i=0; i<=n; ++i) cin >> p[t].x >> p[t++].y;
        for (int i=0; i<=n; ++i) for (int j=0; j<n; ++j) {
            point c = p[j+1] - p[j], v = c.norm();
            double s1 = scale(p[i], p[j], p[j+1], v.rotate(theta)), s2 = scale(p[i], p[j], p[j+1], v.rotate(-theta));
            if (s1>eps && s1<1-eps) p[t++] = p[j] + c*s1;
            if (s2>eps && s2<1-eps) p[t++] = p[j] + c*s2;
        }
        bool vis[N] = {false};
        for (int i=0; i<t; ++i) d[i] = __DBL_MAX__;
        for (int i=0; i<t; ++i) for (int j=0; j<t; ++j) {
            fuel[i][j] = (p[j] - p[i]).len();
            int k;
            for (k=0; k<n; ++k) if (between(p[i], p[k], p[k+1]) && between(p[j], p[k], p[k+1])
                && (p[i]-p[k]).len() < (p[j]-p[k]).len()) break;
            if (k == n) fuel[i][j] *= f;
        }
        d[0] = 0;
        while (true) {
            int x = -1;
            for (int i=0; i<t; ++i) if (!vis[i] && (x==-1 || d[x] > d[i])) x = i;
            if (x == -1) break;
            vis[x] = true;
            for (int i=0; i<t; ++i) if (!vis[i]) d[i] = min(d[i], d[x] + fuel[x][i]);
        }
        cout << "Case " << ++kase << ": " << d[n] << endl;
    }
    return 0;
}