/**
 * UVa1408/LA4018
 * ChengDu 2007
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 9
#define N 50
#define T 39366
int a[N][M], d[2][T], p[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683}, m, n, kase = 0;

void solve() {
    memset(d[0], 0, sizeof(d[0]));
    int c = 0, t = p[m]<<1, r = p[max(m-1, 0)], ans = m*n;
    for (int i=0; i<n; ++i) for (int j=0; j<m; ++j, c^=1) {
        int v, f = i ? a[i-1][j] : 0, l = j ? a[i][j-1] : 0;
        cin >> v; a[i][j] = v = max(v, 0); memset(d[c^1], 1, sizeof(d[0]));
        for (int k=0; k<t; ++k) {
            int h = (k>>1)/r, s = (k>>1)%3, e = (k>>1)%r, b = k&1;
            int &w = d[c^1][6*e], &x = d[c^1][6*e+1], &y = d[c^1][6*e+2], &z = d[c^1][6*e+4];
            w = min(w, d[c][k] + (v && (!l || s || l>=v || b)));
            x = min(x, d[c][k] + (v && (!l || s || l<=v || !b)));
            y = min(y, d[c][k] + (v && (!f || h!=1 || f>=v)));
            z = min(z, d[c][k] + (v && (!f || h!=2 || f<=v)));
        }
    }
    for (int i=0; i<t; ++i) ans = min(ans, d[c][i]);
    cout << "Case " << ++kase << ": " << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m && (m || n)) solve();
    return 0;
}