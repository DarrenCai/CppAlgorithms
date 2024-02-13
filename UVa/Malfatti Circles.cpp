/**
 * UVa1447/LA4642
 * Malfatti 圆
 * Tokyo 2009
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define eps 1e-9
int x, y, x2, y2, x3, y3;

void solve() {
    double a = sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3)), b = sqrt((x-x3)*(x-x3)+(y-y3)*(y-y3)),
        c = sqrt((x2-x)*(x2-x)+(y2-y)*(y2-y)), k1 = sqrt(((b+c)*(b+c)-a*a)/(a*a-(b-c)*(b-c))),
        k2 = sqrt(((a+c)*(a+c)-b*b)/(b*b-(a-c)*(a-c))), k3 = sqrt(((a+b)*(a+b)-c*c)/(c*c-(a-b)*(a-b)));
    double l = eps, r = min(b, c)/k1 - eps, r2, r3, m;
    while (l+eps < r) {
        m = (l+r)/2; r2 = (sqrt(k2*(c-k1*m)+m)-sqrt(m))/k2; r3 = (sqrt(k3*(b-k1*m)+m)-sqrt(m))/k3; r2 *= r2; r3 *= r3;
        k2*r2 + k3*r3 + 2*sqrt(r2*r3) < a ? r = m-eps : l = m+eps;
    }
    cout << r << ' ' << r2 << ' ' << r3 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    while (cin>>x>>y>>x2>>y2>>x3>>y3 && (x || y || x2 || y2 || x3 || y3)) solve();
    return 0;
}
