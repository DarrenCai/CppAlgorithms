/**
 * UVa1319/LA2911
 * SEERC 2006
 */

#include <iostream>
using namespace std;

long long pow(int a, int n) {
    if (n == 0) return 1;
    long long r = pow(a, n>>1);
    return n&1 ? r*r*a : r*r;
}

void solve(int m, int p, int a, int b) {
    int x = (b*a + m) / (a+1), y = (m - b)*a / (a+1);
    long long ans = x*pow(a, p) + y + pow(b*a - a*x + y, p), q = pow(a, p>>1), r = ans%q;
    cout << ans/q + (r*2 >= q) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int m, p, a, b;
    while (cin >> m >> p >> a >> b) solve(m, p, a, b);
    return 0;
}