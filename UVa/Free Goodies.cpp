/**
 * UVa12260/LA4945
 * 免费糖果
 * NWERC 2010
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 1010
struct goody {
    int a, b;
    bool operator< (const goody& rhs) const {
        return a>rhs.a || (a==rhs.a && b<rhs.b);
    }
} g[N];
struct {int a, b;} d[N][N]; char s[8];

void solve() {
    int n; cin >> n >> s;
    for (int i=1; i<=n; ++i) cin >> g[i].a >> g[i].b;
    sort(g+1, g+n+1);
    int p = s[0] == 'P', m = p ? n>>1 : (n+1)>>1;
    if (p) {
        d[1][0].a = g[1].a; d[1][0].b = 0;
    } else {
        d[1][1].a = 0; d[1][1].b = g[1].b;
        if (n-1 >= m) {
            d[1][0].a = g[1].a; d[1][0].b = 0;
        }
    }
    for (int i=2; i<=n; ++i) for (int j = max(m+i-n, 0), k = p ? i>>1 : (i+1)>>1; j<=k; ++j) {
        if (j == 0) {
            d[i][j].a = d[i-1][j].a + g[i].a; d[i][j].b = 0;
        } else {
            d[i][j].a = d[i-1][j-1].a; d[i][j].b = d[i-1][j-1].b + g[i].b;
            if (j <= (p ? (i-1)>>1 : i>>1)) {
                int b = d[i-1][j].b, a = d[i-1][j].a + g[i].a;
                if (b > d[i][j].b || (b==d[i][j].b && a>d[i][j].a)) d[i][j].b = b, d[i][j].a = a;
            }
        }
    }
    cout << d[n][m].a << ' ' << d[n][m].b << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}