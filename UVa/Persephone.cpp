/**
 * UVa10884
 * 外接矩形
 */

#include <iostream>
using namespace std;

#define N 51
__int128_t f[N][N][N][2] = {0};

void print(__int128_t v) {
    if (v > 9) print(v / 10);
    cout << int(v % 10);
}

void solve(int kase) {
    int n; cin >> n;
    cout << "Case #" << kase << ": ";
    if (n&1 || n<4) {
        cout << 0 << endl;
        return;
    }
    n >>= 1;
    __int128_t ans = 0;
    for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j) for (int k=0; k<2; ++k) ans += f[n][i][j][k];
    print(ans);
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int s=2; s<N; ++s) {
        f[s][0][s-1][0] = 1;
        if (s+1 == N) continue;
        for (int i=0; i<s; ++i) for (int j=i+1; j<s; ++j) for (int k=0; k<2; ++k) if (f[s][i][j][k] > 0) {
            for (int a=i; a<j; ++a) for (int b = k ? j : N-2-s+j; b>a; --b) {
                int s1 = s+1 + max(b-j, 0);
                f[s1][a][b][k || b<j] += f[s][i][j][k];
            }
            if (i == 0) for (int m=N-2-s; m>0; --m) for (int b = k ? m+j : N-2-s+j; b>m; --b) {
                int s1 = s+1 + max(b-j, m);
                f[s1][0][b][k || b<m+j] += f[s][i][j][k];
            }
        }
    }
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) solve(kase);
    return 0;
}