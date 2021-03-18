/**
 * UVa1262
 * 密码
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define R 6
#define C 5
char s1[R][C+1], s2[R][C+1], p[C][R], ans[C+1]=""; int t[C+1]={0}, d[C+1][R+1];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int n, k; cin >> n;
    while (n--) {
        cin >> k >> s1[0] >> s1[1] >> s1[2] >> s1[3] >> s1[4] >> s1[5]
            >> s2[0] >> s2[1] >> s2[2] >> s2[3] >> s2[4] >> s2[5];
        bool ok = true;
        for (short c=0; c<C; ++c) {
            p[c][t[c] = 0] = 0;
            for (short i=0, j, l; i<R; ++i) {
                for (j=0; j<R; ++j) if (s1[i][c] == s2[j][c]) break;
                if (j < R) {
                    for (l=0; l<t[c]; ++l) if (p[c][l] == s1[i][c]) break;
                    if (l == t[c]) p[c][t[c]++] = s1[i][c];
                }
            }
            if (t[c] < 1) { ok = false; break; }
            sort(p[c], p[c]+t[c]);
        }
        if (ok) {
            d[C][t[C]] = 1;
            for (short c=C-1; c>=0; --c) {
                d[c][0] = 0; int &ref = d[c+1][t[c+1]];
                for (short j=1; j<=t[c]; ++j) d[c][j] = d[c][j-1] + ref;
            }
            if (k > d[0][t[0]]) {
                cout << "NO" << endl;
                continue;
            }
            for (short c=0, j; c<C; ++c) {
                for (j=t[c]; d[c][j] >= k; --j);
                ans[c] = p[c][j]; k -= d[c][j];
            }
            cout << ans << endl;
        } else cout << "NO" << endl;
    }
    return 0;
}