/**
 * UVa11429
 * 随机数
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 40

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    short r, n;
    while (cin>>r>>n && r) {
        long double ans = .0;
        while (n--) {
            short a, b; cin >> a >> b;
            long double v = 1.l*a/b, d = 1.l;
            for (short i=1; i<=N; ++i) {
                v = v*r;
                d = d*r;
                short j = v + 1e-10;
                ans += 1.l*i*j/d;
                v = v - j;
            }
        }
        cout << ans << endl;
    }
    return 0;
}