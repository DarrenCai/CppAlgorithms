/**
 * UVa12075/LA3295
 * 数三角形
 * Dhaka 2005
 */

#include <iostream>
using namespace std;

#define N 1005
int g[N][N], m, n, kase = 0;

int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else if (b & 1) return gcd(a >> 1, b);
    return gcd(a >> 1, b >> 1) << 1;
}

void solve() {
    long long ans = 0;
    for (int x=1; x<=m; ++x) for (int y=1; y<=n; ++y) ans += (m-x+1)*(n-y+1)*(6ll*x*y - 2*g[x][y]);
    cout << "Case " << ++kase << ": " << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=1; i<N; ++i) for (int j=i; j<N; ++j) g[i][j] = g[j][i] = gcd(i, j);
    while (cin>>m>>n && m) solve();
    return 0;
}