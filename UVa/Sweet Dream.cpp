/**
 * UVa10969
 * 美梦
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

#define N 102
double x[N], y[N], r[N], t[N<<1], pi2 = M_PI + M_PI; int n;

double d(const double& dx, const double& dy) {
    return sqrt(dx*dx + dy*dy);
}

double cvt(const double& v) {
    return v < 0 ? v+pi2 : v;
}

double vis(const int& i, const double& a, const double& b) {
    double c = (a+b)/2, x1 = x[i] + r[i]*cos(c), y1 = y[i] + r[i]*sin(c);
    for (int j=i+1; j<n; ++j) if (d(x1 - x[j], y1 - y[j]) < r[j]) return 0.;
    return (b-a) * r[i];
}

double calc(const int& i) {
    int c = 0;
    for (int j=i+1; j<n; ++j) {
        double dx = x[j]-x[i], dy = y[j]-y[i], d = dx*dx + dy*dy, f = sqrt(d);
        if (f <= r[j]-r[i]) return 0.;
        if (f >= r[i]+r[j] || f <= r[i]-r[j]) continue;
        double a = atan2(dy, dx), b = acos((r[i]*r[i]+d-r[j]*r[j])/r[i]/f/2);
        t[c++] = cvt(a-b); t[c++] = cvt(a+b);
    }
    sort(t, t+c);
    c = unique(t, t+c) - t;
    if (!c) return pi2 * r[i];
    double s = vis(i, t[c-1], t[0]+pi2);
    for (int j=c-2; j>=0; --j) s += vis(i, t[j], t[j+1]);
    return s;
}

void solve() {
    cin >> n;
    for (int i=0; i<n; ++i) cin >> r[i] >> x[i] >> y[i];
    double s = pi2 * r[n-1];
    for (int i=n-2; i>=0; --i) s += calc(i);
    cout << s << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
