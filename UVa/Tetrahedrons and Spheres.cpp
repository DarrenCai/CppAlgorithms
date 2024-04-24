/**
 * UVa11887
 * 球和四面体
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

#define eps 1e-12
#define T 4000
#define M 335
#define N 5
int x[N][4], y[N][4], z[N][4], cx[N], cy[N], cz[N], r[N], c[N], a, b, m, t;
double px[N][5], py[N][5], sx[M], cr[N];

double interp(double x1, double y1, double x2, double y2, double x) {
    return (y1*(x2-x) + y2*(x-x1)) / (x2-x1);
}

void cross(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    double dx = x2-x1, dy = y2-y1, dx1 = x3-x1, dy1 = y3-y1, dx2 = x4-x1, dy2 = y4-y1;
    if ((dx*dy1-dx1*dy)*(dx*dy2-dx2*dy) >= 0.) return;
    dx = x4-x3; dy = y4-y3; dx1 = x1-x3; dy1 = y1-y3; dx2 = x2-x3; dy2 = y2-y3;
    double c1 = dx*dy1-dx1*dy, c2 = dx*dy2-dx2*dy;
    if (c1*c2 >= 0.) return;
    c1 /= c1 - c2; sx[t++] = (1-c1)*x1 + c1*x2;
}

void cross(double x1, double y1, double x2, double y2, int i) {
    double dx = x2-x1, dy = y2-y1, l = sqrt(dx*dx + dy*dy);
    if (l < eps) return;
    double vx = cx[i]-x1, vy = cy[i]-y1; dx /= l; dy /= l;
    double d = abs(dx*vy-vx*dy);
    if (d > cr[i]-eps) return;
    double p = dx*vx+dy*vy, q = sqrt(cr[i]*cr[i]-d*d), p1 = p-q, p2 = p+q;
    if (p1 > -eps && p1 < l+eps) sx[t++] = x1 + dx*p1;
    if (p2 > -eps && p2 < l+eps) sx[t++] = x1 + dx*p2;
}

void cross(int i, int j) {
    double dx = cx[i]-cx[j], dy = cy[i]-cy[j], d = sqrt(dx*dx + dy*dy);
    if (d > cr[i]+cr[j]-eps || d < abs(cr[i]-cr[j])+eps) return;
    double cosa = dx/d, cosb = (cr[j]*cr[j]+d*d-cr[i]*cr[i])/2./cr[j]/d, ss = dy/d*sqrt(1.-cosb*cosb), cc = cosa*cosb;
    sx[t++] = cx[j]+cr[j]*(cc-ss); sx[t++] = cx[j]+cr[j]*(cc+ss);
}

struct trap {
    double h, t, a; int f;
    bool operator< (const trap& rhs) const {
        return t > rhs.t;
    }
} s[N<<2];

void trap(int i, double l, double r) {
    int cc = 0; double h[2];
    for (int j=0; j<c[i]; ++j) {
        double x1 = px[i][j], y1 = py[i][j], x2 = px[i][j+1], y2 = py[i][j+1];
        if (min(x1,x2) > l+eps || max(x1,x2) < r-eps) continue;
        h[cc++] = .5 * (interp(x1, y1, x2, y2, l) + interp(x1, y1, x2, y2, r));
    }
    if (cc != 2) return;
    if (h[0] < h[1]) h[0] += h[1], h[1] = h[0]-h[1], h[0] = h[0]-h[1];
    s[m].h = h[0]; s[m].t = h[0]; s[m].a = 0.; s[m++].f = 1; s[m].h = h[1]; s[m].t = h[1]; s[m].a = 0.; s[m++].f = -1;
}

void trapc(int i, double l, double r) {
    if (max(abs(l-cx[i]), abs(r-cx[i])) > cr[i]+eps) return;
    double d1 = cr[i]*cr[i]-(l-cx[i])*(l-cx[i]), d2 = cr[i]*cr[i]-(r-cx[i])*(r-cx[i]);
    d1 = d1<=0. ? 0. : sqrt(d1); d2 = d2<=0. ? 0. : sqrt(d2);
    double x = .5 * (l+r), d = cr[i]*cr[i]-(x-cx[i])*(x-cx[i]); d = d<=0. ? 0. : sqrt(d);
    double ds = ((l-r)*(l-r) + (d1-d2)*(d1-d2)) / 4., h = sqrt(cr[i]*cr[i]-ds); ds = sqrt(ds);
    double a = cr[i]*cr[i]*asin(ds/cr[i]) - ds*h;
    s[m].h = cy[i] + .5 * (d1 + d2); s[m].t = cy[i] + d; s[m].a = a; s[m++].f = 1;
    s[m].h = cy[i] - .5 * (d1 + d2); s[m].t = cy[i] - d; s[m].a = a; s[m++].f = -1;
}

double area(double h) {
    for (int i=t=0; i<a; ++i) {
        for (int j=c[i]=0; j<4; ++j) {
            if (z[i][j] == h) {
                px[i][c[i]] = x[i][j]; py[i][c[i]++] = y[i][j]; continue;
            }
            for (int k=j+1; k<4; ++k) if (z[i][k] != h) {
                int e = min(z[i][j], z[i][k]), f = max(z[i][j], z[i][k]);
                if (e==f || f<h || e>h) continue;
                px[i][c[i]] = interp(z[i][j], x[i][j], z[i][k], x[i][k], h);
                py[i][c[i]++] = interp(z[i][j], y[i][j], z[i][k], y[i][k], h);
            }
        }
        if (c[i] < 3) continue;
        for (int j=0; j<c[i]; ++j) sx[t++] = px[i][j];
        if (c[i] == 4) {
            double dx = px[i][2] - px[i][0], dy = py[i][2] - py[i][0],
                dx1 = px[i][1] - px[i][0], dy1 = py[i][1] - py[i][0],
                dx2 = px[i][3] - px[i][0], dy2 = py[i][3] - py[i][0], p;
            if ((dx*dy1-dx1*dy)*(dx*dy2-dx2*dy) > 0.) {
                if ((dx1*dy-dx*dy1)*(dx1*dy2-dx2*dy1) > 0.) {
                    p = px[i][1]; px[i][1] = px[i][2]; px[i][2] = px[i][3]; px[i][3] = p;
                    p = py[i][1]; py[i][1] = py[i][2]; py[i][2] = py[i][3]; py[i][3] = p;
                } else
                    p = px[i][2], px[i][2] = px[i][1], px[i][1] = p, p = py[i][2], py[i][2] = py[i][1], py[i][1] = p;
            }
        }
        px[i][c[i]] = px[i][0]; py[i][c[i]] = py[i][0];
    }
    for (int i=0; i<b; ++i) {
        cr[i] = r[i]*r[i] - (cz[i]-h)*(cz[i]-h); cr[i] = cr[i]<=0. ? 0. : sqrt(cr[i]);
        if (cr[i] <= eps) continue;
        sx[t++] = cx[i]; sx[t++] = cx[i]-cr[i]; sx[t++] = cx[i]+cr[i];
    }
    for (int i=0; i<a; ++i) if (c[i] > 2) for (int j=0; j<c[i]; ++j) {
        for (int k=i+1; k<a; ++k) if (c[k] > 2) for (int p=0; p<c[k]; ++p)
            cross(px[i][j], py[i][j], px[i][j+1], py[i][j+1], px[k][p], py[k][p], px[k][p+1], py[k][p+1]);
        for (int k=0; k<b; ++k) if (cr[k] > eps) cross(px[i][j], py[i][j], px[i][j+1], py[i][j+1], k);
    }
    for (int i=0; i<b; ++i) if (cr[i] > eps) for (int j=i+1; j<b; ++j) if (cr[j] > eps) cross(i, j);
    sort(sx, sx+t);
    double ans = 0.;
    for (int i=1; i<t; ++i) if (sx[i]-sx[i-1] > eps) {
        for (int j=m=0; j<a; ++j) if (c[j] > 2) trap(j, sx[i-1], sx[i]);
        for (int j=0; j<b; ++j) if (cr[j] > eps) trapc(j, sx[i-1], sx[i]);
        sort(s, s+m);
        for (int j=0, cc=0; j<m; ++j) {
            if (cc > 0) ans += (sx[i]-sx[i-1]) * (s[j-1].h-s[j].h) + s[j-1].a * s[j-1].f - s[j].a * s[j].f;
            cc += s[j].f;
        }
    }
    return ans;
}

void solve() {
    for (int i=0; i<a; ++i) for (int j=0; j<4; ++j) cin >> x[i][j] >> y[i][j] >> z[i][j];
    for (int i=0; i<b; ++i) cin >> cx[i] >> cy[i] >> cz[i] >> r[i];
    double h = 16./T, s = 0.;
    for (int i=1; i<T; ++i) s += (i&1 ? 4. : 2.) * area(-8.+h*i);
    cout << s*h/3. << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    while (cin >> a >> b && (a || b)) solve();
    return 0;
}