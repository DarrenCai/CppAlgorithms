/**
 * UVa1444/LA4629
 * CERC 2009
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1000200
int a[N], e[N], v[N], r, l;

void solve() {
    cin >> r >> l;
    memset(v, 0, sizeof(v));
    int inf = r * l, ans = inf;
    for (int i=0; i<r; ++i) {
        int n, c = 0; cin >> n;
        for (int j=0, k=0; j<n; ++j) {
            cin >> a[j];
            a[j] ? ++k : e[++c] = k;
        }
        for (int j=0, k=-1, ka=-1, kb=0, s=0; j<l; ++j) {
            if (v[j] == inf) continue;
            while (s <= j) {
                s += max(a[++k], 1);
                a[k] ? ++ka : ++kb;
            }
            if (!a[k]) continue;
            int cc = s-a[k]-kb+c > j ? e[j+1-s+a[k]+kb] - ka : n;
            if (s-kb <= j) cc = min(cc, ka+1-e[j+1-s+kb]);
            cc==n ? v[j] = inf : v[j] += cc;
        }
    }
    for (int i=0; i<l; ++i) ans = min(ans, v[i]);
    cout << ans << endl;
    for (int i=0; i<l; ++i) if (v[i] == ans) cout << i << ' ';
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int z; cin >> z;
    while (z--) solve();
    return 0;
}