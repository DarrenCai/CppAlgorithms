/**
 * UVa1652
 * Fibonacci进制
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define T 65
long long f[T], c[T], d[T];

long long calc(long long n) {
    short i = lower_bound(c, c+T, n) - c;
    if (c[i] == n) return d[i];
    n -= c[i-1];
    long long cnt = d[i-1] + n/i, x = n/i-1;
    while (x > 0) {
        short p = lower_bound(f, f+i-1, x) - f;
        if (f[p] == x) {
            cnt += d[p-1] + 1;
            break;
        }
        cnt += d[p-2] + x-f[p-1]+1;
        x -= f[p-1];
    }
    if (n%i) {
        ++ cnt; x = n/i;
        short r = n%i;
        if (r>2 && x) {
            short p = lower_bound(f, f+i-1, x) - f;
            if (f[p] > x) --p;
            while (i+1-p <= r) {
                ++ cnt;
                p = lower_bound(f, f+p, x-=f[p]) - f;
                if (f[p] > x) --p;
            }
        }
    }
    return cnt;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    f[0] = f[1] = 1; for (short i=2; i<T; ++i) f[i] = f[i-1] + f[i-2];
    c[0] = d[0] = 0;
    for (short i=1; i<T; ++i) {
        c[i] = c[i-1] + i*f[i-1];
        d[i] = d[i-1] + f[i-1] + (i>1 ? d[i-2] : 0);
    }
    f[0] = 0;
    long long n;
    while (cin >> n) cout << calc(n) << endl;
    return 0;
}