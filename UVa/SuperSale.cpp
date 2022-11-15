/**
 * UVa10130
 */

#include <iostream>
using namespace std;

#define W 32
int d[W], n, g;

void solve() {
    cin >> n;
    for (int i=0; i<W; ++i) d[i] = 0;
    for (int i=0; i<n; ++i) {
        int p, w; cin >> p >> w;
        for (int v=W-1; v>=w; --v) d[v] = max(d[v], d[v-w] + p);
    }
    cin >> g;
    int ans = 0;
    for (int i=0; i<g; ++i) {
        int w; cin >> w;
        ans += d[w];
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}