/**
 * UVa1077/LA4127
 * 山的轮廓线
 * World Finals >> 2008 - Banff
 */

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define M 10300
#define N 102
int a[N], n, t, kase = 0; double x[N], h[N], b[N], c[M];

bool cmp(int i, int j) {
    return x[i] - .5*b[i] < x[j] - .5*b[j];
}

void intersect(int i, int j) {
    double s = (b[i]*b[j]*(h[j]-h[i]) + 2*(b[j]*h[i]*x[i]-b[i]*h[j]*x[j])) / 2. / (b[j]*h[i] - b[i]*h[j]);
    if (s > x[i] - .5*b[i] && s < x[i] && s > x[j] - .5*b[j] && s < x[j]) c[t++] = s;
    s = (b[i]*b[j]*(h[j]-h[i]) + 2*(b[i]*h[j]*x[j]+b[j]*h[i]*x[i])) / 2. / (b[i]*h[j] + b[j]*h[i]);
    if (s > x[i] - .5*b[i] && s < x[i] && s > x[j] && s < x[j] + .5*b[j]) c[t++] = s;
    s =  (b[i]*b[j]*(h[i]-h[j]) + 2*(b[i]*h[j]*x[j]+b[j]*h[i]*x[i])) / 2. / (b[i]*h[j] + b[j]*h[i]);
    if (s > x[i] && s < x[i] + .5*b[i] && s > x[j] - .5*b[j] && s < x[j]) c[t++] = s;
    s = (b[i]*b[j]*(h[j]-h[i]) + 2*(b[i]*h[j]*x[j]-b[j]*h[i]*x[i])) /  2. / (b[i]*h[j] - b[j]*h[i]);
    if (s > x[i] && s < x[i] + .5*b[i] && s > x[j] && s < x[j] + .5*b[j]) c[t++] = s;
}

void solve() {
    for (int i=t=0; i<n; ++i) cin >> x[i] >> h[i] >> b[i], a[i] = i;
    sort(a, a+n, cmp);
    for (int i=0; i<n; ++i) {
        c[t++] = x[a[i]] - .5*b[a[i]]; c[t++] = x[a[i]];
        double r = c[t++] = x[a[i]] + .5*b[a[i]];
        for (int j=i+1; j<n; ++j) {
            if (x[a[j]] - .5*b[a[j]] >= r) break;
            intersect(a[i], a[j]);
        }
    }
    sort(c, c+t); t = unique(c, c+t) - c;
    double ans = 0.;
    for (int i=1; i<t; ++i) {
        double x0 = c[i-1], x1 = c[i], m = 0.; int s = -1;
        for (int j=0; j<n; ++j) {
            if (x[a[j]] + .5*b[a[j]] <= x0) continue;
            if (x[a[j]] - .5*b[a[j]] >= x1) break;
            double v = (1. - 2*abs(x[a[j]] - .5*(x0+x1)) / b[a[j]]) * h[a[j]];
            if (s < 0 || v > m) s = a[j], m = v;
        }
        if (s >= 0) ans += sqrt(4*h[s]*h[s]+b[s]*b[s])*(x1-x0)/b[s];
    }
    cout << "Case " << ++ kase << ": " << (long long)(ans+.5) << endl << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}