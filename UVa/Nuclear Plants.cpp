/**
 * UVa1367/LA3532
 * 核电厂
 * CERC 2005
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

#define rs .58
#define rl 1.31
#define eps 1e-9
#define M 40200
#define N 102
#define sqr(x) sqrt(max(x, 0.))
#define aco(x) acos(max(min(x, 1.), -1.))
int xs[N], ys[N], xl[N], yl[N], a[N], b[N], m, n, ks, kl, t, c; double x[M];

struct arc {
   int cx, cy; bool s, t; double y;
   double area(double x1, double x2) const {
      double r = s ? rs : rl, dx1 = x1 - cx, dx2 = x2 - cx,
         y1 = cy - sqr(r*r - dx1*dx1), y2 = cy - sqr(r*r - dx2*dx2), dy1 = y1 - cy, dy2 = y2 - cy;
      double t = aco((dx1*dx2+dy1*dy2)/sqr(dx1*dx1+dy1*dy1)/sqr(dx2*dx2+dy2*dy2));
      return .5 * (r*r*t - abs(dx1*dy2-dx2*dy1));
   }
   double yy(double x) const {
      double r = s ? rs : rl, dx = x - cx;
      return t ? cy + sqr(r*r - dx*dx) : cy - sqr(r*r - dx*dx);
   }
   bool operator< (const arc& rhs) const {
      return y < rhs.y;
   }
} q[N<<2];

bool cmps(int i, int j) {
   return xs[i] < xs[j];
}

bool cmpl(int i, int j) {
   return xl[i] < xl[j];
}

void intersect(int cx1, int cy1, int cx2, int cy2, double r1, double r2) {
   double dx = cx2-cx1, dy = cy2-cy1, d = sqr(dx*dx + dy*dy);
   if (d > r1+r2-eps || d < eps) return;
   double d1 = .5 * (d + (r1*r1 - r2*r2)/d), s = sqr(r1*r1-d1*d1), x0 = cx1 + dx*d1/d;
   d = dy*s/d; x[t++] = x0 - d; x[t++] = x0 + d;
}

void intersect(int cx, int cy, double r) {
   if (cy < r) {
      double s = sqr(r*r-cy*cy); x[t++] = cx - s; x[t++] = cx + s;
   }
   if (cy + r > m) {
      double s = sqr(r*r-(m-cy)*(m-cy)); x[t++] = cx - s; x[t++] = cx + s;
   }
}

void add_arc(int cx, int cy, bool s, double x) {
   double r = s ? rs : rl;
   if (abs(x-cx) > r-eps) return;
   double d = sqr(r*r-(x-cx)*(x-cx));
   if (cy > d) q[c++] = {cx, cy, s, false, cy-d};
   if (cy+d < m) q[c++] = {cx, cy, s, true, cy+d};
}

double solve() {
   for (int i=t=0; i<ks; ++i) {
      cin >> xs[i] >> ys[i], x[t++] = xs[i]-rs, x[t++] = xs[i]+rs, a[i] = i, intersect(xs[i], ys[i], rs);
      for (int j=0; j<i; ++j) intersect(xs[i], ys[i], xs[j], ys[j], rs, rs);
   }
   for (int i=0; i<kl; ++i) {
      cin >> xl[i] >> yl[i], x[t++] = xl[i]-rl, x[t++] = xl[i]+rl, b[i] = i, intersect(xl[i], yl[i], rl);
      for (int j=0; j<i; ++j) intersect(xl[i], yl[i], xl[j], yl[j], rl, rl);
      for (int j=0; j<ks; ++j) intersect(xs[j], ys[j], xl[i], yl[i], rs, rl);
   }
   x[t++] = 0.; x[t++] = n; sort(a, a+ks, cmps); sort(b, b+kl, cmpl); sort(x, x+t);
   double s = m*n; int h1 = 0, h2 = 0;
   for (int i=1; i<t; ++i) {
      double x1 = x[i-1], x2 = x[i], xc = .5*(x1+x2); c = 0;
      if (x1 > x2-eps || x1 < -eps || x2 > n+eps) continue;
      while (h1 < ks && xs[a[h1]]+rs < x1-eps) ++h1;
      for (int j=h1; j<ks && xs[a[j]]-rs < x2+eps; ++j) add_arc(xs[a[j]], ys[a[j]], true, xc);
      while (h2 < kl && xl[b[h2]]+rl < x1-eps) ++h2;
      for (int j=h2; j<kl && xl[b[j]]-rl < x2+eps; ++j) add_arc(xl[b[j]], yl[b[j]], false, xc);
      sort(q, q+c);
      for (int j=0, cc=0; j<c; ++j) if (q[j].t) {
         if (cc) {
            if (--cc == 0) s -= q[j].area(x1, x2) + .5*(x2-x1)*(q[j].yy(x1)+q[j].yy(x2));
         } else s -= q[j].area(x1, x2) + .5*(x2-x1)*(q[j].yy(x1)+q[j].yy(x2));
      } else if (++cc == 1) s -= q[j].area(x1, x2) - .5*(x2-x1)*(q[j].yy(x1)+q[j].yy(x2)-(j==c-1 ? 2.*m : 0.));
   }
   return s;
}

int main() {
   // freopen("in.txt", "r", stdin);
   // freopen("ou.txt", "w", stdout);
   cout << fixed << setprecision(2);
   while (cin >> n >> m >> ks >> kl && (n || m || ks || kl)) cout << solve() << endl;
   return 0;
}