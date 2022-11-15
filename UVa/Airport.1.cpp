/**
 * UVa1450
 * 机场
 */

#include <iostream>
using namespace std;

#define N 5020
int a[N], b[N], n;

bool check(int s) {
    int ta = 0, tb = 0, c = 0;
    for (int i=1; i<n; ++i) {
        int fa = max(a[i]-s, 0);
        int fb = max(b[i]-s, 0);
        ta = min(min(a[i-1], ta+1), i);
        tb = min(min(b[i-1], tb+1), i);
        c = min(min(ta+tb, c+1), i);
        if (fa>ta || fb>tb || fa+fb>c) return false;
    }
    return true;
}

void solve() {
    cin >> n >> a[0] >> b[0];
    for (int i=1; i<n; ++i) {
        cin >> a[i] >> b[i];
        a[i] += a[i-1]; b[i] += b[i-1];
    }
    int l = max(max(a[0], b[0]), 1), r = max(max(a[n-1], b[n-1]), 1);
    while (l < r) {
        int mid = (l+r) >> 1;
        check(mid) ? r = mid : l = mid+1;
    }
    cout << l-1 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}