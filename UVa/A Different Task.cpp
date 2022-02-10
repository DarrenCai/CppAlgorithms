/**
 * UVa10795
 * 新汉诺塔问题
 */

#include <iostream>
using namespace std;

#define N 63
short s[N], t[N]; long long f[N][3][2], h[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    h[0] = 0; for (short i=1; i<N; ++i) h[i] = 2*h[i-1] + 1;
    f[0][0][0] = f[0][0][1] = f[0][1][0] = f[0][1][1] = f[0][2][0] = f[0][2][1] = 0;
    short kase = 0, n;
    while (cin>>n && n) {
        for (short i=1; i<=n; ++i) cin >> s[i], --s[i];
        for (short i=1; i<=n; ++i) cin >> t[i], --t[i];
        while (n && s[n]==t[n]) --n;
        for (short i=1; i<=n; ++i) for (short j=0; j<3; ++j) {
            f[i][j][0] = s[i]==j ? f[i-1][j][0] : f[i-1][3-j-s[i]][0] + 1 + h[i-1];
            f[i][j][1] = t[i]==j ? f[i-1][j][1] : f[i-1][3-j-t[i]][1] + 1 + h[i-1];
        }
        short i = 3-s[n]-t[n];
        long long ans = n ? f[n-1][i][0] + 1 + f[n-1][i][1] : 0;
        cout << "Case " << ++kase << ": " << ans << endl;
    }
    return 0;
}