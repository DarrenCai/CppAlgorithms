/**
 * UVa12119/LA4060
 * 敲钟
 * Dhaka 2007
 */

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define M 25
#define N 1000000
long long n; const double f = 1./3; int g[M+1][M+1], fac[M+1][9], t[M+1] = {0}, kase = 0;

struct sol {
    int t1, t2, t3;
    bool operator< (const sol& rhs) const {
        return t1<rhs.t1 || (t1==rhs.t1 && t2<rhs.t2) || (t1==rhs.t1 && t2==rhs.t2 && t3<rhs.t3);
    }
    bool operator== (const sol& rhs) const {
        return t1==rhs.t1 && t2==rhs.t2 && t3==rhs.t3;
    }
} ans[8000];

int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    if (a == 1) return 1;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else {
        if (b & 1) return gcd(a >> 1, b);
        return gcd(a >> 1, b >> 1) << 1;
    }
}

void solve() {
    int c = 0;
    for (int d1=1; d1<M; ++d1) for (int d2=d1+1; d2<=M; ++d2) for (int d3=d2-d1, i=0; i<t[d1]; ++i)
    for (int g1=fac[d1][i], j=0; j<t[d2]; ++j) for (int g2=fac[d2][j], k=0; k<t[d3]; ++k) {
        int g3 = fac[d3][k], gg = g[g[g1][g2]][g3], x = pow(g1*g2*g3/gg * 1.0*n, f)+1, y = max(x-M-2, 1);
        x = min(x, N);
        for (int gm = max(g1, g2), t1 = x-x%gm; t1>=y; t1 -= gm) {
            int t2 = t1+d1, t3 = t1+d2;
            if (t3>N || t1*(long long)t2*t3/g1*gg/g2/g3!=n || gcd(d1, t1)!=g1 || gcd(d2, t1)!=g2 || gcd(d3, t2)!=g3) continue;
            ans[c].t1 = t1; ans[c].t2 = t2; ans[c++].t3 = t3;
        }
    }
    sort(ans, ans+c);
    c = unique(ans, ans+c) - ans;
    cout << "Scenario " << ++kase << ":" << endl;
    if (c == 0) cout << "Such bells don't exist" << endl;
    for (int i=0; i<c; ++i) cout << ans[i].t1 << ' ' << ans[i].t2 << ' ' << ans[i].t3 << endl;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=1; i<=M; ++i) for (int j=i; j>0; --j) if (i%j == 0) fac[i][t[i]++] = j;
    for (int i=1; i<=M; ++i) for (int j=i; j<=M; ++j) g[i][j] = g[j][i] = gcd(i, j);
    ios::sync_with_stdio(false);
    while (cin>>n && n) solve();
    return 0;
}