/**
 * UVa1338/LA3193
 * Ehime 2004
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define N 5
int a[N], b[N], n, t; double x[N], y[N];

double interp(double x1, double x2, double y1, double y2, double x) {
    return ((x2-x)*y1 + (x-x1)*y2)/(x2-x1);
}

double area2() {
    double s = y[0] * (x[1] - x[t-1]) + y[t-1] * (x[0] - x[t-2]);
    for (int i=t-2; i>0; --i) s += y[i] * (x[i+1] - x[i-1]);
    return s;
}

void solve() {
    double s = 0.;
    for (int i=0; i<n; ++i) cin >> a[i] >> b[i];
    a[n] = a[0]; b[n] = b[0];
    for (int i=0; i<n; ++i) {
        int c = min(b[i], b[i+1]), d = max(b[i], b[i+1]);
        if (c == d) {
            double l=10., r=0., v=0.;
            for (int j=0; j<n; ++j) {
                int e = max(min(b[j], b[j+1]), c), f = min(max(b[j], b[j+1]), d);
                if (e > f) continue;
                double g = interp(b[j], b[j+1], a[j], a[j+1], e), h = interp(b[j], b[j+1], a[j], a[j+1], e);
                l = min(l, min(g, h)); r = max(r, max(g, h));
                if (b[j] == b[j+1]) v += abs(a[j+1]-a[j]);
            }
            if (l < r) s += (2.*(r-l)-v)*abs(a[i+1]-a[i]);
        } else {
            for (int j=t=0; j<n; ++j) {
                int e = max(min(b[j], b[j+1]), c), f = min(max(b[j], b[j+1]), d);
                if (e > f) continue;
                if (e == f) {
                    if (e == b[j]) x[t] = a[j], y[t++] = b[j];
                    continue;
                }
                if (b[j] > b[j+1]) e = e + f, f = e - f, e = e - f; 
                if (e != b[j+1]) x[t] = interp(b[j], b[j+1], a[j], a[j+1], e), y[t++] = e;
                if (f != b[j+1]) x[t] = interp(b[j], b[j+1], a[j], a[j+1], f), y[t++] = f;
            }
            int dy = a[i+1]-a[i], dz = abs(b[i+1]-b[i]);
            if (t > 2) s += area2()*sqrt(dy*dy+dz*dz)/dz;
        }
    }
    cout << s << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    while (cin >> n && n) solve();
    return 0;
}