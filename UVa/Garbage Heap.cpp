/**
 * UVa10755
 * 废料堆
 * 边多级降维边递推
 */

#include <iostream>
using namespace std;

#define N 25
long long v[N][N][N], s[N][N], ss[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        int a, b, c; cin >> a >> b >> c;
        for (int x=0; x<a; ++x) for (int y=0; y<b; ++y) for (int z=0; z<c; ++z) cin >> v[x][y][z];
        long long ans = 1ll << 63;
        for (int y0=0; y0<b; ++y0) for (int z0=0; z0<c; ++z0) {
            for (int x=0; x<a; ++x) for (int y=y0; y<b; ++y) s[x][y] = 0;
            for (int z=z0; z<c; ++z) {
                for (int x=0; x<a; ++x) ss[x] = 0;
                for (int y=y0; y<b; ++y) {
                    long long sum = 0, mx = 0;
                    for (int x=0; x<a; ++x) {
                        s[x][y] += v[x][y][z];
                        ss[x] += s[x][y];
                        sum += ss[x];
                        ans = max(ans, sum - mx);
                        mx = min(mx, sum);
                    }
                }
            }
        }
        cout << ans << endl;
        if (t) cout << endl;
    }
    return 0;
}