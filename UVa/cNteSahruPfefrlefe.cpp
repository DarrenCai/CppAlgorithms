/**
 * UVa1041/LA3272
 * 近乎完美的洗牌
 * World Finals 2005
 */

#include <iostream>
using namespace std;

const int m=10, n = 52; int a[m+1][n], b[m+1][n], p[n], as[m], ae[m], s[m], e[m], ad, at, d, t, kase = 0;

int h(int k, int s) {
    int c = 0;
    for (int i=0; i<n; ++i) if (a[k][b[s][i]] != p[i]) ++c;
    return (c+1) >> 1;
}

bool IDAStar(int k = 0, int c = 0) {
    if (c == d) {
        for (int i=0, s=t-k; i<n; ++i) if (a[k][b[s][i]] != p[i]) return false;
        return true;
    } else for (int i=0, j=n-1; i<j; ++i) for (int x=k+1; c+1+t-x >= d; ++x) {
        for (int u=0; u<n; ++u) a[x][u] = a[k][b[x-k][u]];
        swap(a[x][i], a[x][i+1]); s[c] = x; e[c] = i;
        if (c + h(x, t-x) < d && IDAStar(x, c+1)) return true;
    }
    return false;
}

bool cmp() {
    for (int i=0; i<d; ++i) if (e[i] != ae[i]) return e[i] < ae[i];
    return false;
}

void solve() {
    for (int i=0; i<n; ++i) cin >> p[i], a[0][i] = i;
    for (t=1, ad=m+1; t<=m; ++t) {
        if (ad) for (d=0; d<=t; ++d) if (IDAStar()){
            if (d < ad || (d == ad && cmp())) {
                for (int i=0; i<d; ++i) as[i] = s[i], ae[i] = e[i];
                ad = d; at = t;
            }
            break;
        }
    }
    cout << "Case " << ++kase << endl;
    cout << "Number of shuffles = " << at << endl;
    if (ad > 0) {
        for (int i=0; i<ad; ++i) cout << "Error in shuffle " << as[i] << " at location " << ae[i] << endl;
    } else cout << "No error in any shuffle" << endl;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=0; i<n; ++i) b[0][i] = i;
    for (int i=1, k=n>>1; i<=m; ++i) {
        for (int j=0; j<k; ++j) b[i][j<<1 | 1] = b[i-1][j];
        for (int j=k; j<n; ++j) b[i][(j-k)<<1] = b[i-1][j];
    }
    int t; cin >> t;
    while (t--) solve();
    return 0;
}