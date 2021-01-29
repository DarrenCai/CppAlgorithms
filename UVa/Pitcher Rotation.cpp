/**
 * UVa1379
 * 棒球投手
 * 本题存疑，详见 https://www.cnblogs.com/jionkitten/p/12984866.html
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 105
// #define M 33     // 坑啊，题目说m不超过30的
#define G 220
short n, m, g, p[G], dp[2][6][6][6][6];
struct node {
    short p, s;
    bool operator< (const node& rhs) const {
        return s > rhs.s;
    }
} s[N][N]={0};  // s[M]][N]={0}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        cin >> n >> m >> g; g+=10;
        for (short i=1; i<=m; ++i) {
            for (short j=1; j<=n; ++j) cin >> s[i][j].s, s[i][j].p = j;
            sort(s[i]+1, s[i]+1+n);
        }
        for (short i=0; i<g; ++i) cin >> p[i];
        short cur = 0, nex = 1, a, b, c, d, e, aa, bb, cc, dd, ee, ans = 0, r;
        for (a = p[g-=4]==0 ? 0 : 1; aa = s[p[g]][a].p, a<6; ++a) {
            for (b = p[g+1]==0 ? 0 : 1; bb = s[p[g+1]][b].p, b<6; ++b) if (b==0 || aa!=bb) {
                for (c = p[g+2]==0 ? 0 : 1; cc = s[p[g+2]][c].p, c<6; ++c) if (c==0 || (aa!=cc && bb!=cc)) {
                    for (d = p[g+3]==0 ? 0 : 1; dd = s[p[g+3]][d].p, d<6; ++d)
                        if (d==0 || (aa!=dd && bb!=dd && cc!=dd)) {
                            dp[cur][a][b][c][d] = s[p[g]][a].s + s[p[g+1]][b].s + s[p[g+2]][c].s + s[p[g+3]][d].s;
                            if (d==0) break;
                        }
                    if (c==0) break;
                }
                if (b==0) break;
            }
            if (a==0) break;
        }
        while (--g >= 0) {
            for (a = p[g]==0 ? 0 : 1; aa = s[p[g]][a].p, a<6; ++a) {
                for (b = p[g+1]==0 ? 0 : 1; bb = s[p[g+1]][b].p, b<6; ++b) if (b==0 || aa!=bb) {
                    for (c = p[g+2]==0 ? 0 : 1; cc = s[p[g+2]][c].p, c<6; ++c) if (c==0 || (aa!=cc && bb!=cc)) {
                        for (d = p[g+3]==0 ? 0 : 1; dd = s[p[g+3]][d].p, d<6; ++d)
                            if (d==0 || (aa!=dd && bb!=dd && cc!=dd)) {
                                short &ref = dp[nex][a][b][c][d] = 0;
                                for (e = p[g+4]==0 ? 0 : 1; ee = s[p[g+4]][e].p, e<6; ++e)
                                    if (e==0 || (aa!=ee && bb!=ee && cc!=ee && dd!=ee)) {
                                        ref = max(int(ref), s[p[g]][a].s + dp[cur][b][c][d][e]);
                                        if (g==0) ans = max(ans, ref);
                                        if (e==0) break;
                                    }
                                if (d==0) break;
                            }
                        if (c==0) break;
                    }
                    if (b==0) break;
                }
                if (a==0) break;
            }
            cur ^= 1; nex ^= 1;
        }
        r = ans % 100;
        cout << ans/100 << (r < 10 ? ".0" : ".") << r << endl;
    }
    return 0;
}