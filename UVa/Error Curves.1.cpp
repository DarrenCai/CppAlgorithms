/**
 * UVa1476/LA5009
 * 误差曲线
 * ChengDu 2010
 */

#include <cstdio>
#include <algorithm>
using namespace std;

#define N 10010
int a[N], b[N], c[N], n;

double f(double x) {
    double ans = a[0]*x*x + b[0]*x + c[0];
    for (int i=1; i<n; ++i) ans = max(ans, a[i]*x*x + b[i]*x + c[i]);
    return ans;
}

void solve() {
    scanf("%d", &n);
    for (int i=0; i<n; ++i) scanf("%d%d%d", &a[i], &b[i], &c[i]);
    double low = 0., high = 1000.;
    for (int i=0; i<70; ++i) {
        double m1 = (low+low+high)/3, m2 = (low+high+high)/3;
        f(m1) < f(m2) ? high = m2 : low = m1;
    }
    printf("%.4lf\n", f(high));
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}