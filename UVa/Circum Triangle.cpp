/**
 * UVa11186
 * 圆周上的三角形
 */

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define N 510
double t[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n, r;
    while (cin>>n>>r && (n || r)) {
        for (short i=0; i<n; ++i) cin >> t[i];
        if (n<3 || r==0) {
            cout << 0 << endl;
        } else {
            sort(t, t+n);
            double s = .0, p = .5*r*r, c = M_PI/180;
            for (short i=0; i<n; ++i) for (short j=i+1; j<n; ++j)
                s += p*sin(c*(t[j]-t[i]))*(n-2*(j-i));
            cout << (long long)(s+.5) << endl;
        }
    }
    return 0;
}