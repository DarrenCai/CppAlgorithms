/**
 * UVa11426
 * 最大公约数之和——极限版II
 */

#include <iostream>
using namespace std;

#define N 4000000
long long p[N+1], f[N+1]; int n;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=1; i<=N; ++i) f[i] = p[i] = 0;
    for (int i=2; i<=N; ++i) if (!p[i]) for (int j=i; j<=N; j+=i) {
        if (!p[j]) p[j] = j;
        p[j] = p[j] / i * (i-1);
    }
    for (int i=N>>1; i>0; --i) for (int j=N/i; j>1; --j) f[i*j] += i*p[j];
    for (int i=2; i<=N; ++i) f[i] += f[i-1];
    while (cin>>n && n) cout << f[n] << endl;
    return 0;
}