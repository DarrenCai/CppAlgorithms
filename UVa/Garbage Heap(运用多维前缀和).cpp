/**
 * UVa10755
 * 废料堆
 */

#include <iostream>
using namespace std;

#define N 25
long long s[N][N][N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=0; i<N; ++i) for (int j=0; j<N; ++j) s[0][i][j] = s[i][0][j] = s[i][j][0] = 0;
    short t; cin >> t;
    while (t--) {
        int a, b, c; cin >> a >> b>> c; ++a; ++b; ++c;
        for (int x=1; x<a; ++x) for (int y=1; y<b; ++y) for (int z=1; z<c; ++z) {
            cin >> s[x][y][z];
            s[x][y][z] += s[x-1][y][z] + s[x][y-1][z] + s[x][y][z-1]
                - s[x-1][y-1][z] - s[x-1][y][z-1]- s[x][y-1][z-1] + s[x-1][y-1][z-1];
        }
        long long ans = 1ll << 63;
        for (int y0=1; y0<b; ++y0) for (int y=y0; y<b; ++y) for (int z0=1; z0<c; ++z0) for (int z=z0; z<c; ++z) {
            long long sum = 0, mx = 0;
            for (int x=1; x<a; ++x) {
                sum = s[x][y][z] - s[x][y0-1][z] - s[x][y][z0-1] + s[x][y0-1][z0-1];
                ans = max(ans, sum - mx);
                mx = min(mx, sum);
            }
        }
        cout << ans << endl;
        if (t) cout << endl;
    }
    return 0;
}