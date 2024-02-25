/**
 * UVa1463/LA4818
 * SEERC 2010
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

#define eps 1e-5
#define N 2005
int x[N], y[N], x2[N], y2[N], n; double p[N], p1[N], p2[N], d1[N], d2[N], s;
struct intv {
    double a, b;
    bool operator< (const intv& rhs) const {
        return a<rhs.a;
    }
} t[N];

bool check(double r) {
    int c = 0; double a = s, b = 0.;
    for (int i=0; i<n; ++i) {
        if (y[i] == y2[i]) {
            if (r <= abs(y[i])) continue;
            double d = sqrt(r*r - y[i]*y[i]); a = x[i] - d; b = x2[i] + d;
        } else if (x[i] == x2[i]) {
            double d = s;
            if (y[i] > 0) {
                if (y[i] >= r) continue;
                d = sqrt(r*r - y[i]*y[i]);
            } else if (y2[i] < 0) {
                if (-y2[i] >= r) continue;
                d = sqrt(r*r - y2[i]*y2[i]);
            }
            a = x[i] - d; b = x[i] + d;
        } else if (p2[i] <= 0.) {
            if (r <= abs(y2[i])) continue;
            double d = sqrt(r*r - y2[i]*y2[i]); a = x2[i] - d; b = x2[i] + d;
        } else if (p1[i] >= s) {
            if (r <= abs(y[i])) continue;
            double d = sqrt(r*r - y[i]*y[i]); a = x[i] - d; b = x[i] + d;
        } else if (p[i] >= p1[i] && p[i] <= p2[i]) {
            a = d1[i] >= r ? r/d1[i]*(p1[i]-p[i]) + p[i] : (p1[i] > 0. ? x[i] - sqrt(r*r - y[i]*y[i]) : -.1);
            b = d2[i] >= r ? r/d2[i]*(p2[i]-p[i]) + p[i] : (p2[i] < s ? x2[i] + sqrt(r*r - y2[i]*y2[i]) : s + .1);
        } else if (max(d1[i], d2[i]) <= r) {
            a = p1[i] > 0. ? x[i] - sqrt(r*r - y[i]*y[i]) : -.1;
            b = p2[i] < s ? x2[i] + sqrt(r*r - y2[i]*y2[i]) : s + .1;
        } else if (min(d1[i], d2[i]) >= r) {
            if (d1[i] < d2[i]) {
                if (r <= abs(y[i])) continue;
                double d = sqrt(r*r - y[i]*y[i]); a = x[i] - d; b = x[i] + d;
            } else {
                if (r <= abs(y2[i])) continue;
                double d = sqrt(r*r - y2[i]*y2[i]); a = x2[i] - d; b = x2[i] + d;
            }
        } else if (d1[i] < d2[i]) {
            a = p1[i] > 0. ? x[i] - sqrt(r*r - y[i]*y[i]) : -.1;
            b = p1[i] + (p2[i]-p1[i])*(r-d1[i])/(d2[i]-d1[i]);
        } else {
            a = p1[i] + (p2[i]-p1[i])*(r-d1[i])/(d2[i]-d1[i]);
            b = p2[i] < s ? x2[i] + sqrt(r*r - y2[i]*y2[i]) : s + .1;
        }
        if (a < 0. && b > s) return false;
        if (a < b) t[c].a = a, t[c++].b = b;
    }
    if (c == 0) return true;
    sort(t, t+c);
    for (int i=b=0; i<n; ++i) {
        if (t[i].a >= b) return true;
        if ((b = max(t[i].b, b)) > s) return false;
    }
    return true;
}

void solve() {
    cin >> n >> s;
    for (int i=0, t; i<n; ++i) {
        cin >> x[i] >> y[i] >> x2[i] >> y2[i];
        if (y[i] == y2[i]) {
            if (x[i] > x2[i]) t = x[i], x[i] = x2[i], x2[i] = t;
        } else if (x[i] == x2[i]) {
            if (y[i] > y2[i]) t = y[i], y[i] = y2[i], y2[i] = t;
        } else {
            if (x[i] > x2[i]) t = x[i], x[i] = x2[i], x2[i] = t, t = y[i], y[i] = y2[i], y2[i] = t;
            double k = (y2[i]-y[i])/double(x2[i]-x[i]); p1[i] = max(k*y[i]+x[i], 0.); p2[i] = min(k*y2[i]+x2[i], s);
            if (p1[i] < s && p2[i] > 0) {
                double l = sqrt((x[i] - x2[i]) * (x[i] - x2[i]) + (y[i] - y2[i]) * (y[i] - y2[i]));
                p[i] = x[i] - (x2[i] - x[i]) * double(y[i]) / (y2[i] - y[i]);
                d1[i] = abs((p1[i]-x[i])*(y2[i]-y[i])+(x2[i]-x[i])*y[i]) / l;
                d2[i] = abs((p2[i]-x[i])*(y2[i]-y[i])+(x2[i]-x[i])*y[i]) / l;
            }
        }
    }
    double l = 0., r = 36056.;
    while (l + eps < r) {
        double m = (l+r)/2;
        check(m) ? l = m : r = m-eps;
    }
    cout << r << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(3);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
