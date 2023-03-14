/**
 * UVa12253/LA4998
 * 简单加密法
 * Kuala Lumper 2010
 * 有点暴力的解法(*´∇｀*)
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 1000000000000
#define N 1000000
long long p1[N], p2[N], p[N], k1, kase = 0;

long long pow(long long a, long long n) {
    __int128_t x = a; long long ans = 1;
    for (long long i=n; i; i>>=1, x = x*x%M) if (i&1) ans = ans*x % M;
    return ans;
}

long long solve() {
    if (k1%10 == 0) return M;
    if (k1%5 == 0) {
        long long b = 244140625, s = (M/10 + b-1)/b, c = b<<1;
        if (~s & 1) ++s;
        for (long long k2=s*b; k2<M; k2+=c) if (pow(k1, k2) == k2) return k2;
    }
    memset(p, 0, sizeof(p));
    p1[1] = k1; p[k1] = 1;
    for (int i=2; i<N; ++i) {
        p1[i] = k1*p1[i-1] % N;
        if (p[p1[i]]) {
            for (int g = i-p[p1[i]], r = p[p1[i]], j=0; j<g; ++j) if ((p1[r+j]-r-j) % g == 0) {
                memset(p, 0, sizeof(p));
                __int128_t x = pow(k1, N), y = pow(k1, p1[r+j]) % M;
                for (int k=1; k<N; ++k) {
                    y = x*y % M; p2[k] = y/N;
                    if (p[p2[k]]) {
                        for (int g2 = k-p[p2[k]], r2 = p[p2[k]], j2=0; j2<g2; ++j2)
                            if (10*p2[r2+j2]>=N && (p2[r2+j2]-r2-j2) % g2 == 0) return p2[r2+j2]*N + p1[r+j];
                        return 0;
                    } else p[p2[k]] = k;
                }
                return 0;
            }
            return 0;
        } else p[p1[i]] = i;
    }
    return 0;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>k1 && k1) cout << "Case " << ++kase <<": Public Key = " << k1 << " Private Key = " << solve() << endl;
    return 0;
}