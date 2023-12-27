/**
 * UVa1462/LA4769
 * Harbin 2009
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 3000060
#define C 26
#define L 12
int s[N][C], c[N], d[L][L], m, e, t; char p[L];

int query(int u, int n) {
    if (d[m][n] <= e) return c[u];
    int cc = 0; ++n;
    for (int i=0; i<C; ++i) if (s[u][i]) {
        int ed = d[0][n];
        for (int j=1; j<=m; ++j)
            ed = min(d[j][n] = i == p[j-1]-'a' ? d[j-1][n-1] : min(min(d[j][n-1], d[j-1][n]), d[j-1][n-1]) + 1, ed);
        if (ed <= e) cc += query(s[u][i], n);
    }
    return cc;
}

void solve() {
    int n; cin >> n;
    for (int i=0; i<L; ++i) d[i][0] = d[0][i] = i;
    memset(s[0], c[t = 0] = 0, sizeof(s[0]));
    while (n--) {
        cin >> p;
        for (int i=0, x=0; p[i]; ++i) {
            int &r = s[x][p[i]-'a'];
            r ? ++c[x = r] : (memset(s[r = ++t], 0, sizeof(s[0])), c[x = r] = 1);
        }
    }
    cin >> n;
    while (n--) {
        cin >> p >> e; m = strlen(p);
        cout << query(0, 0) << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}