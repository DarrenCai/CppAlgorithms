/**
 * UVa10003
 * 切木棍
 * 利用四边形不等式优化时间复杂度到O(n^2)
 */

#include <iostream>
using namespace std;

#define N 55
int l, n, c[N], d[N][N], k[N][N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> l && l) {
        cin >> n; for (int i=0; i<n; ++i) cin >> c[i];
        for (int s=0; s<n; ++s) for (int i=0, j; (j=i+s) < n; ++i) {
            int len = (j+1<n ? c[j+1] : l) - (i>0 ? c[i-1] : 0);
            if (s == 0) {
                d[i][j] = len; k[i][j] = i;
            } else {
                int k1 = k[i][j-1], v; d[i][j] = len + d[i][k1-1] + d[k1+1][j]; k[i][j] = k1;
                while (++k1 <= k[i+1][j]) if ((v = len + d[i][k1-1] + d[k1+1][j]) < d[i][j])
                    d[i][j] = v, k[i][j] = k1;
            }
        }
        cout << "The minimum cutting is " << d[0][n-1] << '.' << endl;
    }
    return 0;
}