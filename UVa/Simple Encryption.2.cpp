/**
 * UVa12253/LA4998
 * 简单加密法
 * Kuala Lumper 2010
 * 不动点迭代：初始时随机选取一个超过10^12的数，如1000000000007，
 *           将其代入计算，如果f(x)!=x，那么令x=f(x)，如此循环，能在短时间内找出合法解。
 */

#include <iostream>
using namespace std;

#define M 1000000000000
long long k1, kase = 0;

long long pow(long long a, long long n) {
    __int128_t x = a; long long ans = 1;
    for (long long i=n; i; i>>=1, x = x*x%M) if (i&1) ans = ans*x % M;
    return ans;
}

long long solve() {
    long long k2 = M + 7;
    while (pow(k1, k2) != k2%M) k2 = pow(k1, k2);
    return k2;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>k1 && k1) cout << "Case " << ++kase <<": Public Key = " << k1 << " Private Key = " << solve() << endl;
    return 0;
}