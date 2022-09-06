/**
 * UVa12235/LA4490
 * 帮助布布
 * Wuhan 2009
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 110
int d[2][N][256][9], b[256], kase = 0, n, k;

void solve() {
    memset(d[0], 1, sizeof(d[0])); d[0][0][0][8] = 0;
    int pre = 0, cur = 1, ss = 0;
    for (int i=1; i<=n; ++i) {
        memset(d[cur], 1, sizeof(d[cur]));
        int a; cin >> a; a -= 25; ss |= 1<<a;
        for (int j=min(i-1, k); j>=0; --j) for (int m=0; m<256; ++m) for (int p=0; p<9; ++p) if (d[pre][j][m][p] < N) {
            if (j<k) d[cur][j+1][m][p] = min(d[cur][j+1][m][p], d[pre][j][m][p]);
            int &ref = d[cur][j][m | 1<<a][a];
            ref = min(ref, (a!=p) + d[pre][j][m][p]);
        }
        pre ^= 1; cur ^= 1;
    }
    int (&ref)[256][9] = d[pre][k], ans = n;
    for (int i=0; i<256; ++i) for (int j=0; j<9; ++j) if (ref[i][j] < ans) {
        ans = min(ans, ref[i][j] + b[ss^i]);
    }
    cout << "Case " << ++kase << ": " << ans << endl << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=0; i<256; ++i) {
        int x = i; b[i] = 0;
        while (x > 0) ++b[i], x -= x&(-x);
    }
    while (cin>>n>>k && n) solve();
    return 0;
}