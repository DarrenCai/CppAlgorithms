/**
 * UVa12237/LA4492
 * 佳佳的机器人
 * Wuhan 2009
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

#define sqr(x) sqrt(max(x, 0.))
#define aco(x) acos(max(min(x, 1.), -1.))
#define eps 1e-9
int x1, y, x2, y2, x3, y3, x4, y4, t, kase = 0; double x[22], cx[4], cy[4], r[4];

struct arc {
    int i; double y1, y2, y; bool up;
    bool operator< (const arc& rhs) const {
        return y < rhs.y;
    }
    double area(double x1, double x2) const {
        double dx1 = x1 - cx[i], dx2 = x2 - cx[i], dy1 = y1 - cy[i], dy2 = y2 - cy[i];
        return .5 * (r[i]*r[i]*aco((dx1*dx2+dy1*dy2)/r[i]/r[i]) - abs(dx1*dy2-dx2*dy1));
    }
} a[10];

void intersect(int i, int j) {
    double dx = cx[j]-cx[i], dy = cy[j]-cy[i], d = sqrt(dx*dx + dy*dy);
    if (d < eps || d > r[i]+r[j]-eps || d < max(r[i], r[j]) - min(r[i], r[j]) + eps) return;
    double d1 = .5 * (d + (r[i]*r[i] - r[j]*r[j])/d), s = sqr(r[i]*r[i]-d1*d1), x0 = cx[i] + dx*d1/d;
    d = dy*s/d; x[t++] = x0 - d; x[t++] = x0 + d;
}

bool valid(double x, double y) {
    int c = 0;
    for (int i=0; i<4; ++i) if (sqrt((x-cx[i])*(x-cx[i]) + (y-cy[i])*(y-cy[i])) > r[i]-eps) ++c;
    return c > 0 && c < 4;
}

void solve() {
    cx[0] = .5*(x1+x3); cy[0] = .5*(y+y3); r[0] = .5*sqrt((x1-x3)*(x1-x3) + (y-y3)*(y-y3));
    cx[1] = .5*(x1+x4); cy[1] = .5*(y+y4); r[1] = .5*sqrt((x1-x4)*(x1-x4) + (y-y4)*(y-y4));
    cx[2] = .5*(x2+x3); cy[2] = .5*(y2+y3); r[2] = .5*sqrt((x2-x3)*(x2-x3) + (y2-y3)*(y2-y3));
    cx[3] = .5*(x2+x4); cy[3] = .5*(y2+y4); r[3] = .5*sqrt((x2-x4)*(x2-x4) + (y2-y4)*(y2-y4));
    for (int i=0; i<4; ++i) x[i] = cx[i] - r[i], x[i+4] = cx[i] + r[i];
    t = 8;
    for (int i=0; i<4; ++i) for (int j=i+1; j<4; ++j) intersect(i, j);
    sort(x, x+t);
    double s = 0, xp = x[0];
    for (int i=1; i<t; xp = x[i++]) if (x[i] - xp > eps) {
        int c = 0;
        for (int j=0; j<4; ++j) if (xp > cx[j]-r[j]-eps && x[i] < cx[j]+r[j]+eps) {
            double xc = .5*(xp + x[i]), d = sqr(r[j]*r[j] - (xc-cx[j])*(xc-cx[j]));
            double d1 = sqr(r[j]*r[j] - (xp-cx[j])*(xp-cx[j])), d2 = sqr(r[j]*r[j] - (x[i]-cx[j])*(x[i]-cx[j]));
            a[c++] = {j, cy[j]-d1, cy[j]-d2, cy[j]-d, false}; a[c++] = {j, cy[j]+d1, cy[j]+d2, cy[j]+d, true};
        }
        sort(a, a+c);
        for (int j=1; j<c; ++j) if (valid(.5*(xp+x[i]), .5*(a[j].y+a[j-1].y))) {
            s += .5*(x[i]-xp)*abs(a[j].y1+a[j].y2-a[j-1].y1-a[j-1].y2);
            a[j].up ? s += a[j].area(xp, x[i]) : s -= a[j].area(xp, x[i]);
            a[j-1].up ? s -= a[j-1].area(xp, x[i]) : s += a[j-1].area(xp, x[i]);
        }
    }
    cout << "Case " << ++kase << ": " << s << endl << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    while (cin >> x1 >> y >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 && 
            (x1 || y || x2 || y2 || x3 || y3 || x4 || y4)) solve();
    return 0;
}