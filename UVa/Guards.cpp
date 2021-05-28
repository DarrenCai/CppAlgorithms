/**
 * UVa12371
 * 守卫
 */

#include <iostream>
using namespace std;

#define N 100010
#define K 52
#define M 1000000007

int d[N][K+1] = {0};

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    d[2][1] = 1;
    for (int n=3; n<N; ++n) for (short k=1, m=min(n>>1,K); k<=m; ++k)
        d[n][k] = (n*(n-1ll)%M * d[n-1][k] + n*(n-1ll)*(n-1)/2%M * d[n-2][k-1]) % M;
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) {
        int n, k; cin >> n >> k;
        cout << "Case " << kase << ": " << d[n][k] << endl;
    }
    return 0;
}
