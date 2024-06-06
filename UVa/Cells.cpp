/**
 * UVa1357/LA3486
 * Hangzhou 2005
 */

#include <iostream>
using namespace std;

#define M 300050
#define N 20000100
int lv[N], fa[N], anc[M][19], m, n, t;

bool query() {
    int a, b; cin >> a >> b;
    if (b == 0) return false;
    int k = lv[b = fa[b]] - lv[a], i = 1;
    while ((1<<i) <= k) ++i;
    while (--i >= 0) if ((1<<i) <= k) b = anc[b][i], k -= 1<<i;
    return b == a;
}

void solve() {
    cin >> n; lv[0] = t = 0;
    for (int i=0; i<n; ++i) {
        int c; cin >> c;
        for (int j=0; j<c; ++j) lv[++t] = lv[i]+1, fa[t] = i;
    }
    for (int i=1; i<n; ++i) anc[i][0] = fa[i];
    for (int j=1, k=lv[n-1]; (1<<j) <= k; ++j) for (int i=1; i<n; ++i) if ((1<<j) <= lv[i])
        anc[i][j] = anc[anc[i][j-1]][j-1];
    cin >> m;
    while (m--) cout << (query() ? "Yes" : "No") << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) {
        if (k > 1) cout << endl;
        cout << "Case " << k << ':' << endl;
        solve();
    }
    return 0;
}