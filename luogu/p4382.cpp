/**
 * P4382 [八省联考 2018] 劈配
 */

#include <iostream>
#include <cstring>
using namespace std;

#define C 11
#define N 202
int w[N][N][C], c[N][N], py[N][N], px[N], rx[N], rk[N], b[N], t[N], s[N], m, n; bool vis[N];

bool match(int i, int j, int s) {
    if (i < s) rk[s] = max(rk[s], i);
    for (int k=0, d; k < c[i][j]; ++k) {
        if (vis[d = w[i][j][k]]) continue;
        vis[d] = true;
        if (t[d] < b[d]) {
            px[i] = d; rx[i] = j; py[d][t[d]++] = i;
            return true;
        }
        for (int p=0; p < b[d]; ++p) if (match(py[d][p], rx[py[d][p]], s)) {
            px[i] = j; rx[i] = j; py[d][p] = i;
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> n >> m; memset(c, 0, sizeof(c));
    for (int i=1; i<=m; ++i) cin >> b[i], t[i] = 0;
    for (int i=1; i<=n; ++i) {
        px[i] = -1; rx[i] = m+1;
        for (int j=1; j<=m; ++j) {
            int a; cin >> a;
            if (a) w[i][a][c[i][a]++] = j;
        }
    }
    for (int i=1; i<=n; ++i) cin >> s[i];
    for (int i=1; i<=n; ++i) {
        memset(vis, rk[i] = 0, sizeof(vis));
        for (int j=1; j<=m; ++j) if (match(i, j, j<=s[i] ? i : 0)) {
            if (j <= s[i]) rk[i] = i;
            break;
        }
        if (i > 1) cout << ' ';
        cout << rx[i];
    }
    cout << endl;
    for (int i=1; i<=n; ++i) {
        if (i > 1) cout << ' ';
        cout << i - rk[i];
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t, _; cin >> t >> _;
    while (t--) solve();
    return 0;
}