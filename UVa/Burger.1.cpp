/**
 * UVa557
 * 汉堡
 * 求反,然后存储系数能提速
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define N 100011
long double d[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    d[0] = .0;
    for (int i=1; i<N; ++i) d[i] += d[i-1] + log(1.l*i);
    const long double c = log(.5l);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n; n -= 2;
        cout << 1. - exp(c*n + d[n] - d[n>>1]*2) << endl;
    }
    return 0;
}