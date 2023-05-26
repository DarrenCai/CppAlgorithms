/**
 * UVa12164/LA4412
 * 伟大的游戏--石头剪刀布
 * Kuala Lumpur 2008
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define G 1020
int g, w, l; double d[G][G<<1], p[G][3];

bool check(double qw, double ql) {
    d[g][0] = d[g][g+1] = 0.; for (int i=1; i<=g; ++i) d[g][i] = qw, d[g][i+g+1] = ql;
    for (int i=g-1; i>=0; --i) {
       double e0 = p[i][2]*d[i+1][1] + p[i][0]*d[i+1][0] + p[i][1]*d[i+1][g+2];
       double e1 = p[i][0]*d[i+1][1] + p[i][1]*d[i+1][0] + p[i][2]*d[i+1][g+2];
       double e2 = p[i][1]*d[i+1][1] + p[i][2]*d[i+1][0] + p[i][0]*d[i+1][g+2];
       d[i][0] = d[i][g+1] = max(max(e0, e1), e2);
       for (int j=1; j<=i; ++j) {
           e0 = p[i][2]*d[i+1][j+1] + p[i][0]*d[i+1][j] + p[i][1]*d[i+1][j-1];
           e1 = p[i][0]*d[i+1][j+1] + p[i][1]*d[i+1][j] + p[i][2]*d[i+1][j-1];
           e2 = p[i][1]*d[i+1][j+1] + p[i][2]*d[i+1][j] + p[i][0]*d[i+1][j-1];
           d[i][j] = max(max(e0, e1), e2);
           e0 = p[i][2]*d[i+1][j+g] + p[i][0]*d[i+1][j+g+1] + p[i][1]*d[i+1][j+g+2];
           e1 = p[i][0]*d[i+1][j+g] + p[i][1]*d[i+1][j+g+1] + p[i][2]*d[i+1][j+g+2];
           e2 = p[i][1]*d[i+1][j+g] + p[i][2]*d[i+1][j+g+1] + p[i][0]*d[i+1][j+g+2];
           d[i][j+g+1] = max(max(e0, e1), e2);
       }
    }
    return d[0][0] > 0.;
}

double solve() {
    for (int i=0; i<g; ++i) {
       cin >> p[i][0] >> p[i][1] >> p[i][2];
       p[i][0] /= 100.; p[i][1] /= 100.; p[i][2] /= 100.;
    }
    double low = 0., high = 1.;
    while (low + 1e-8 <= high) {
       double mid = (low + high) / 2;
       check(1-mid, -mid) ? low = mid : high = mid;
    }
    if (high == .5) return 1.*l/(w+l);
    double k = (1.-high) / high;
    return (1.-pow(k, l)) / (1. - pow(k, w+l));
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    while (cin>>g>>w>>l && g) cout << 100*solve() << '%' << endl;
    return 0;
}