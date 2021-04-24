/**
 * UVa766
 * 幂之和
 */

#include <iostream>
using namespace std;

#define N 22
int c[N][N];

int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a < 0) return gcd(-a, b);
    if (a == 0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else {
        if (b & 1) return gcd(a >> 1, b);
        return gcd(a >> 1, b >> 1) << 1;
    }
}

struct f {
    int n=0, d=1;
    void redu() {
        int g = gcd(d, n); d /= g; n /= g;
    }
    const f from(int n1, int d1) {
        n = n1; d = d1;
        if (n) redu();
        return *this;
    }
    void sub(const f& rhs) {
        if (rhs.n == 0) return;
        int g = gcd(d, rhs.d);
        n = rhs.d/g*n - d/g*rhs.n; d *= rhs.d/g;
        redu();
    }
} a[N], ff;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short i=0; i<N; ++i) {
        c[i][0] = 1;
        for (short j=1; j<=i; ++j) c[i][j] = c[i][j-1]*(i-j+1)/j;
    }
    short t; cin >> t;
    while (t--) {
        short k; cin >> k; int m = 1;
        for (short i=k+1; i>0; --i) {
            a[i].n = c[k][i-1]; a[i].d = 1;
            for (short j=k+1; j>i; --j) a[i].sub(ff.from(a[j].n*c[j][i-1], a[j].d));
            a[i].d *= c[i][i-1]; a[i].redu();
            if (a[i].n) m *= a[i].d/gcd(m, a[i].d);
        }
        cout << m;
        for (short i=k+1; i>=0; --i) cout << ' ' << m/a[i].d*a[i].n;
        cout << endl;
        if (t) cout << endl;
    }
    return 0;
}
