/**
 * UVa12253/LA4998
 * 简单加密法
 * Kuala Lumper 2010
 * 自相似性质：如果K1^K2 ≡ K2 mod 10^12，那么有K1^(k2%10^i) ≡ K2%10^i，i≤12
 */

#include <iostream>
using namespace std;

long long p[13], k1, kase = 0;

long long pow_mod(long long a, long long n, long long m) {
    __int128_t x = a; long long ans = 1;
    for (long long i=n; i; i>>=1, x = x*x%m) if (i&1) ans = ans*x % m;
    return ans;
}

long long dfs(int c = 0, long long k = 0) {
    if (c == 12) return pow_mod(k1, k, p[12])==k ? k: 0;
    for (int i=c<11 ? 0 : 1; i<10; ++i) {
        long long t = p[c]*i + k, x;
        if (pow_mod(k1, t, p[c]) == t%p[c]) if (x = dfs(c+1, t)) return x;
    }
    return 0;
}

long long solve() {
    if (k1%10 == 0) return p[12];
    return dfs();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    p[0] = 1; for (int i=1; i<13; ++i) p[i] = 10*p[i-1];
    while (cin>>k1 && k1) cout << "Case " << ++kase <<": Public Key = " << k1 << " Private Key = " << solve() << endl;
    return 0;
}