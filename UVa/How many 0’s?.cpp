/**
 * UVa11038
 * 有多少个0
 */

#include <iostream>
using namespace std;

#define N 12
long long p[N];

long long solve(long long m, long long n, int a, int b) {
    if (a == b) {
        if (a == 1) return m == 0;
        int x = m/p[a-1], y = n/p[a-1];
        m %= p[a-1]; n %= p[a-1];
        if (x == y) return (n-m+1)*(x==0) + solve(m, n, a-1, a-1);
        long long ans = (p[a-1]-m)*(x==0) + solve(m, p[a-1]-1, a-1, b-1) + solve(0, n, a-1, b-1);
        if (++x < y) ans += (y-x)*solve(0, p[a-1]-1, a-1, b-1);
        return ans;
    }
    long long ans = solve(m, p[a]-1, a, a);
    while (++a < b) ans += solve(p[a]/10, p[a]-1, a, a);
    return ans + solve(p[a]/10, n, a, a);
}

void solve(long long m, long long n) {
    int a = 0, b = 0;
    for (long long x=m; x>0; x/=10) ++a;
    for (long long x=n; x>0; x/=10) ++b;
    cout << solve(m, n, max(a, 1), max(b, 1)) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    p[0] = 1; for (int i=1; i<N; ++i) p[i] = 10*p[i-1];
    long long m, n;
    while (cin>>m>>n && m>=0) solve(m, n);
    return 0;
}