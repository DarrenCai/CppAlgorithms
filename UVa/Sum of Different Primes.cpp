/**
 * UVa1213
 * 不同素数之和
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1121
#define C 200
#define K 15
bool flag[N] = {false}; short prim[C], idx[N], c=0; int d[N][K][C];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short i=2; i<34; ++i) if (!flag[i]) for (short j=i*i; j<N; j+=i) flag[j] = true;
    for (short i=2; i<N; ++i) if (!flag[i]) idx[prim[c] = i] = c, c++;
    memset(d, 0, sizeof(d));
    for (short i=2; i<N; ++i) {
        if (!flag[i] && i>1) d[i][1][idx[i]] = 1;
        for (short j=2; j<K; ++j) for (short k=0, m=i/j; k<c && prim[k]<=m; ++k) {
            for (short l=k+1, ii=i-prim[k], n=ii/(j-1); l<c && prim[l]<=n; ++l) d[i][j][k] += d[ii][j-1][l];
        }
    }
    short n, k;
    while (cin>>n>>k && n && k) {
        int ans = 0;
        for (short i=0, m=n/k; i<c && prim[i]<=m; ++i) ans += d[n][k][i];
        cout << ans << endl;
    }
    return 0;
}