/**
 * UVa1642
 * 魔法GCD
 */

#include <iostream>
using namespace std;

#define L 20
struct mgcd{struct {int i; long long g;} e[L]; short l;} q[2];

long long gcd(long long a, long long b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else {
        if (b & 1) return gcd(a >> 1, b);
        return gcd(a >> 1, b >> 1) << 1;
    }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        long long ans = q[0].l = q[1].l = 0;
        int n; cin >> n;
        for (int i=0; i<n; ++i) {
            long long a; cin >> a;
            mgcd &qp = q[i&1], &qc = q[(i&1)^1]; short &l = qc.l = 0;
            for (short j=0; j<qp.l; ++j) {
                long long g = gcd(qp.e[j].g, a);
                if (l<1 || qc.e[l-1].g < g) {
                    qc.e[l].i = qp.e[j].i;
                    qc.e[l++].g = g;
                    ans = max(ans, g *= (i-qp.e[j].i+1));
                }
            }
            if (l<1 || qc.e[l-1].g < a) qc.e[l].i = i, qc.e[l++].g = a, ans = max(ans, a);
        }
        cout << ans << endl;
    }
    return 0;
}