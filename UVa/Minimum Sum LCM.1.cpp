/**
 * UVa10791
 * 和最小的LCM
 */

#include <iostream>
using namespace std;

#define M 65536
unsigned int prim[M], m = 0, n, kase = 0; bool f[M] = {0};

unsigned int solve() {
    unsigned int ans = 0, c = 0;
    for (int i=0; i<m && prim[i]*prim[i]<=n; ++i) if (n%prim[i] == 0) {
        int x = 1;
        while (n%prim[i] == 0) x *= prim[i], n /= prim[i];
        ++ c; ans += x;
    }
    if (n > 1) ans += n, ++c;
    return c<1 ? 2 : (c<2 ? ans+1 : ans);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<M; ++i) if (!f[i]) {
        for (int j=i<<1; j<M; j+=i) f[j] = true;
        prim[m++] = i;
    }
    while (cin>>n && n) cout << "Case " << ++kase << ": " << solve() << endl;
    return 0;
}