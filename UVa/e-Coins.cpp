/**
 * UVa10306
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 42
#define S 302
int d[S][S], a[N], b[N], n, s, s2;

void solve() {
    cin >> n >> s; s2 = s*s;
    for (int i=0; i<n; ++i) cin >> a[i] >> b[i];
    memset(d, -1, sizeof(d)); d[0][0] = 0;
    int ans = -1;
    for (int x=0; x<s; ++x) for (int y=0; x*x+y*y<s2; ++y) if (d[x][y] >= 0) for (int i=0; i<n; ++i) {
        int e = x+a[i], f = y+b[i], v = e*e+f*f;
        if (e<=s && e<=s && v<=s2) {
            d[e][f] = d[e][f] < 0 ? d[x][y]+1 : min(d[e][f], d[x][y]+1);
            if (v == s2) ans = ans < 0 ? d[e][f] : min(ans, d[e][f]);
        }
    }
    ans < 0 ? cout << "not possible" << endl : cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}