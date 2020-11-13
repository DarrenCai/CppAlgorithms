/**
 * UVa1628
 * 送匹萨
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 100

int d[N][N][2][N], p[N], e[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n; cin >> n;
    while (cin >> n) {
        short x = 0; int ans = 0;
        for (short i=0; i<n; ++i) {
            cin >> p[i]; if (p[x] < 0 && p[i] > 0) x = i;
        }
        for (short i=0; i<n; ++i) cin >> e[i];
        if (x == 0) {
            if (p[0] > 0) {
                for (short i=0; i<n; ++i) ans += max(e[i]-p[i], 0);
            } else {
                for (short i=0; i<n; ++i) ans += max(e[i]+p[i], 0);
            }
        } else {
            memset(d, 0, sizeof(d));
            for (short k=1; k<n; ++k) for (short i=0; i<n; ++i) for (short j=i; j<n && j-i+k<n; ++j) {
                for (short l=i-1; l>=0 && j-l+k<=n; --l) {
                    d[i][j][0][k] = max(d[i][j][0][k], d[l][j][0][k-1] + e[l]-(p[i]-p[l])*k);
                    d[i][j][1][k] = max(d[i][j][1][k], d[l][j][0][k-1] + e[l]-(p[j]-p[l])*k);
                }
                for (short l=j+1; l<n && l-i+k<=n; ++l) {
                    d[i][j][0][k] = max(d[i][j][0][k], d[i][l][1][k-1] + e[l]-(p[l]-p[i])*k);
                    d[i][j][1][k] = max(d[i][j][1][k], d[i][l][1][k-1] + e[l]-(p[l]-p[j])*k);
                }
            }
            for (short i=0; i<n; ++i) for (short k=1; k<=n; ++k) {
                ans = max(ans, d[i][i][0][k-1]+e[i]-p[i]*(i>=x ? k : -k));
            }
        }
        cout << ans << endl;
    }
}