/**
 * UVa1638
 * 杆子的排列
 */

#include <iostream>
using namespace std;

#define N 20
long long c[N+1][N+1], p[N+1][N+1], d[N+1][N+1];
#define cc(n, i) (n<i ? 0 : c[n][i])
#define dd(n, i) (n<i ? 0 : d[n][i])

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    p[0][0] = c[0][0] = 1;
    for (short i=1; i<=N; ++i) {
        c[i][0] = p[i][0] = 1; c[i][1] = p[i][1] = i;
        for (short j=2; j<=i; ++j) {
            c[i][j] = c[i-1][j-1] + c[i-1][j];
            p[i][j] = i*p[i-1][j-1];
        }
    }
    d[0][0] = 1;
    for (short i=1; i<=N; i++) {
        d[i][1] = p[i-1][i-1];
        for (short j=2; j<=i; ++j) {
            d[i][j] = 0;
            for (short k=i-j; k>=0; --k) d[i][j] += p[i-1][k]*d[i-k-1][j-1];
        }
    }
    short t; cin >> t;
    while (t--) {
        short n, l, r; cin >> n >> l >> r;
        if (l > 1) {
            long long s = 0; for (short i=l-1; i<=n-r; ++i) s += cc(n-1, i) * dd(i, l-1) * dd(n-i-1, r-1);
            cout << s << endl;
        } else cout << dd(n-1, r-1) << endl;
    }
    return 0;
}