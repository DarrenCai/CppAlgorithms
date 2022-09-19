/**
 * UVa1443/LA4625
 * 花环
 * CERC 2009
 */

#include <iostream>
using namespace std;

#define N 40100
#define M 10050
int n, m, d, w[N]={0}, dp[N][2];

bool check(int x) {
    for (int i=0; i<=n; i+=2) dp[i][0] = dp[i][1] = M;
    dp[0][0] = 0;
    for (int i=2; i<=n; i+=2) for (int j=1, ii; j<=d && (ii=i-(j<<1)) >= 0; ++j) {
        if (w[i]-w[i-j] > x) break;
        if (w[i-j]-w[ii] > x) continue;
        dp[i][0] = min(dp[i][0], dp[ii][1]+1);
        dp[i][1] = min(dp[i][1], dp[ii][0]+1);
    }
    return dp[n][m&1] <= m;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    short z; cin >> z;
    while (z--) {
        cin >> n >> m >> d; --m;
        for (int i=1; i<=n; ++i) cin >> w[i], w[i] += w[i-1];
        if (n&1 || m*d<<1 < n || n < m<<1) {
            cout << "BAD" << endl;
        } else {
            int l = 1, r = w[n];
            while (l < r) {
                int x = (l+r) >> 1;
                check(x) ? r = x : l = x+1;
            }
            cout << l << endl;
        }
    }
    return 0;
}