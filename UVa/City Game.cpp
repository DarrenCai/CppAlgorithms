/**
 * UVa1330
 * 最⼤⼦矩阵
 */

#include <iostream>
using namespace std;

#define N 1010
char s[N]; short u[2][N], l[2][N], r[2][N], m, n;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        cin >> m >> n;
        int ans = 0;
        for (short i=0; i<m; ++i) {
            short c = i&1, p = 1^c, left=-1, right=n;
            for (short j=0; j<n; ++j) {
                cin >> s[j];
                if (s[j] == 'R') {
                    u[c][j] = 0; left = j; l[c][j] = -1;
                } else {
                    u[c][j] = 1 + (i>0 ? u[p][j] : 0);
                    l[c][j] = i>0 ? max(l[p][j], left) : left;
                }
            }
            for (short j=n-1; j>=0; --j) {
                if (s[j] == 'R') {
                    right = j; r[c][j] = n;
                } else {
                    r[c][j] = i>0 ? min(r[p][j], right) : right;
                    ans = max(ans, u[c][j]*(r[c][j]-l[c][j]-1));
                }
            }
        }
        cout << 3*ans << endl;
    }
    return 0;
}