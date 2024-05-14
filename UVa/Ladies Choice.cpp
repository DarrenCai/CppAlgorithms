/**
 * UVa1175/LA3989
 * 女士的选择
 * SWERC 2007
 */

#include <iostream>
using namespace std;

#define N 1005
int x[N][N], y[N][N], px[N], py[N], q[N*N], n;

void solve() {
    cin >> n;
    int head = 0, tail = 0;
    for (int i=1; i<=n; ++i) {
        px[i] = 0; q[tail++] = i;
        for (int j=0; j<n; ++j) cin >> x[i][j];
    }
    for (int i=1; i<=n; ++i) {
        y[i][py[i] = 0] = n;
        for (int j=0, s; j<n; ++j) cin >> s, y[i][s] = j;
    }
    while (head < tail) {
        int i = q[head++], s = x[i][px[i]++];
        if (y[s][i] < y[s][py[s]]) {
            if (py[s]) q[tail++] = py[s];
            py[s] = i;
        } else q[tail++] = i;
    }
    for (int i=1; i<=n; ++i) cout << x[i][px[i]-1] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int i=0; i<t; ++i) {
        if (i) cout << endl;
        solve();
    }
    return 0;
}