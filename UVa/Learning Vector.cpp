/**
 * UVa12589
 * 学习向量
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define N 60
struct vec {
    short x, y;
    bool operator< (const vec& rhs) const {
        return x * rhs.y < rhs.x * y;
    }
} v[N];
short dd[N]; int d[N][N][N*N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        short n, k; cin >> n >> k;
        for (short i=0; i<n; ++i) cin >> v[i].x >> v[i].y;
        sort(v, v+n);
        dd[n] = 0; for (short i=n-1; i>=0; --i) dd[i] = v[i].x + dd[i+1];
        memset(d, -1, sizeof(d));
        for (short i=0; i<n; ++i) d[i][1][v[i].x] = v[i].x * v[i].y;
        for (short l=1; l<=k; ++l) for (short i=n-l; i>=0; --i) for (short w=1, j=i+1; w<=dd[j]; ++w) {
            if (d[j][l][w] > d[i][l][w]) d[i][l][w] = d[j][l][w];
            if (d[j][l-1][w] > -1) {
                int &ref = d[i][l][w + v[i].x];
                ref = max(ref, 2*w*v[i].y + v[i].x*v[i].y + d[j][l-1][w]);
            }
        }
        int ans = 0;
        for (short w=1; w<=dd[0]; ++w) ans = max(ans, d[0][k][w]);
        cout << "Case " << kase << ": " << ans << endl;
    }
    return 0;
}