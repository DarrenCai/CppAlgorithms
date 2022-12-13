/**
 * UVa11762
 * 得到1
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define M 1001
#define N 1000010
double d[N] = {0}; bool f[N] = {0}; int prim[M], s[N], c = 0;

double dp(int n) {
    if (n==1 || d[n]) return d[n];
    int v = n, t = 0;
    for (int i=0; i<c && prim[i]<v; ++i) if (v%prim[i] == 0) {
        d[n] += dp(n / prim[i]); ++t;
        while (v%prim[i] == 0) v /= prim[i];
    }
    if (v > 1) d[n] += dp(n / v), ++t;
    return d[n] = (d[n] + s[n]) / t;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(10);
    s[1] = 0;
    for (int i=2; i<M; ++i) if (!f[i]) {
        for (int j=i<<1; j<N; j+=i) f[j] = true;
        prim[c++] = i;
    }
    for (int i=2; i<N; ++i) s[i] += s[i-1] + !f[i];
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) {
        int n; cin >> n;
        cout << "Case " << kase << ": " << dp(n) << endl;
    }
    return 0;
}