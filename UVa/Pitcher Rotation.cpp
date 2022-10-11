/**
 * UVa1379/LA3679
 * 棒球投手
 * Asia Kaohsiung 2006
 * 本题存疑，详见 https://www.cnblogs.com/jionkitten/p/12984866.html
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 105
#define G 220
#define X 6         // #define X 10
int f[G][X][X][X][X], y[G];
struct node {
    short p, s;
    bool operator< (const node& rhs) const {
        return s > rhs.s;
    }
} s[N][N]={0};

int p(int x, int i) {
    if (x < 0) return 0;
    return i>0 || !y[x] ? s[y[x]][i].p : -1;
}

void solve() {
    int n, m, g, ans = 0; cin >> n >> m >> g; g+=9;
    for (int i=1; i<=m; ++i) {
        for (int j=1; j<=n; ++j) cin >> s[i][j].s, s[i][j].p = j;
        sort(s[i]+1, s[i]+1+n);
    }
    int t = min(X, n+1);
    for (int x=0; x<=g; ++x) {
        cin >> y[x];
        for (int a=0; a<t; ++a) {
            int pa = p(x-3, a);
            if (pa < 0) continue;
            for (int b=0; b<t; ++b) {
                int pb = p(x-2, b);
                if (pb < 0 || (pb && pb==pa)) continue;
                for (int c=0; c<t; ++c) {
                    int pc = p(x-1, c);
                    if (pc < 0 || (pc && (pc==pa || pc==pb))) continue;
                    for (int d=0; d<t; ++d) {
                        int pd = p(x, d);
                        if (pd < 0 || (pd && (pd==pa || pd==pb || pd==pc))) continue;
                        int &r = f[x+1][a][b][c][d] = 0;
                        for (int e = x>3 && y[x-4] ? 1 : 0; e<t; ++e) {
                            int pe = x<4 ? 0 : s[y[x-4]][e].p;
                            if (pe && (pe==pa || pe==pb || pe==pc || pe==pd)) continue;
                            r = max(r, f[x][e][a][b][c] + s[y[x]][d].s);
                        }
                        if (x == g) ans = max(ans, r);
                    }
                }
            }
        }
    }
    cout << ans/100;
    ans %= 100;
    cout << (ans < 10 ? ".0" : ".") << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int a=0; a<X; ++a) for (int b=0; b<X; ++b)
        for (int c=0; c<X; ++c) for (int d=0; d<X; ++d) f[0][a][b][c][d] = 0;
    short t; cin >> t;
    while (t--) solve();
    return 0;
}