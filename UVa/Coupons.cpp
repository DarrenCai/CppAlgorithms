/**
 * UVa10288
 * 优惠券
 * 抽卡问题：https://zhuanlan.zhihu.com/p/150899532
 */

#include <iostream>
using namespace std;

#define N 35

struct {long long n, d;} f[N];

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

short bits(long long v) {
    long long c=1; short i=1;
    while ((c*=10) <= v) ++i;
    return i;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    f[1].n = f[1].d = 1;
    for (short i=2; i<N; ++i) {
        f[i].d = f[i-1].d*(i-1);
        f[i].n = f[i-1].n*i + f[i].d;
        long long g = gcd(f[i].d, f[i].n);
        f[i].n /= g;
        f[i].d /= g;
    }
    short n;
    while (cin>>n) {
        long long i = f[n].n / f[n].d, r = f[n].n % f[n].d;
        if (r > 0) {
            short j = bits(i);
            for (short k=j; k>=0; --k) cout << ' ';
            cout << r << endl << i << ' ';
            for (short k=bits(f[n].d); k>0; --k) cout << '-';
            cout << endl;
            for (short k=j; k>=0; --k) cout << ' ';
            cout << f[n].d << endl;
        } else cout << i << endl;
    }
    return 0;
}