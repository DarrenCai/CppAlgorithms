/**
 * UVa1436/LA4390
 * 堆计数
 * CERC 2008
 */

#include <iostream>
using namespace std;

#define M 708
#define N 500050
int prim[N], pf[N][20], c[N], fa[N], f[N] = {0}, x[N] = {0}, t = 0;

int pow_mod(int p, int n, int m) {
    if (n == 0) return 1%m;
    long long r = pow_mod(p, n>>1, m);
    r = r*r % m;
    return n&1 ? r*p%m : r;
}

void solve() {
    int m, n, cc = 0;
    cin >> n >> m;
    for (int i=2; i<=n; ++i) c[i] = 1, f[i] = 0, cin >> fa[i];
    for (int i=n; i>1; --i) if (fa[i] < i) c[fa[i]] += c[i];
    for (int i=2; i<n; ++i) {
        for (int j=0; j<x[i]; ++j) ++f[pf[i][j]];
        if (c[i] > 1) for (int j=0; j<x[c[i]]; ++j) --f[pf[c[i]][j]];
    }
    long long ans = 1;
    for (int i=0; i<t && prim[i]<n; ++i) if (f[prim[i]]) ans = ans*pow_mod(prim[i], f[prim[i]], m)%m;
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cout.tie(0); cin.tie(0);
    for (int i=2; i<M; ++i) if (!f[i]) {
        prim[t++] = i;
        for (int j=i; j<N; j+=i) {
            f[j] = 1;
            for (int k=j; k%i==0; k/=i) pf[j][x[j]++] = i;
        }
    }
    for (int i=M; i<N; ++i) if (!f[i]) {
        prim[t++] = i;
        for (int j=i; j<N; j+=i) pf[j][x[j]++] = i;
    }
    int t; cin >> t;
    while (t--) solve();
    return 0;
}