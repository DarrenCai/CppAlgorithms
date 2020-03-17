/**
 * UVa10003
 * 切木棍
 */

#include <iostream>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define N 55
int l, n, c[N], d[N][N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> l && l) {
        cin >> n; for (int i=0; i<n; ++i) cin >> c[i];
        for (int s=0; s<n; ++s) for (int i=0, j; (j=i+s) < n; ++i) {
            int len = (j+1<n ? c[j+1] : l) - (i>0 ? c[i-1] : 0);
            if (s == 0) {
                d[i][j] = len;
            } else {
                d[i][j] = len + d[i+1][j];
                d[i][j] = min(d[i][j], len + d[i][j-1]);
                for (int k=i+1; k<j; ++k) d[i][j] = min(d[i][j], len + d[i][k-1] + d[k+1][j]);
            }
        }
        cout << "The minimum cutting is " << d[0][n-1] << '.' << endl;
    }
    return 0;
}