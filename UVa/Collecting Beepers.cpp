/**
 * UVa10496
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 12
int a[N], x[N], y[N], x0, y0, w, h, n;

short solve() {
    cin >> w >> h >> x0 >> y0 >> n;
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i], a[i] = i;
    int ans = 500;
    do {
        int v = abs(x[a[n-1]]-x0) + abs(y[a[n-1]]-y0) + abs(x[a[0]]-x0) + abs(y[a[0]]-y0);
        for (int i=1; i<n; ++i) v += abs(x[a[i]]-x[a[i-1]]) + abs(y[a[i]]-y[a[i-1]]);
        ans = min(ans, v);
    } while (next_permutation(a, a+n));
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << "The shortest path has length " << solve() << endl;
    return 0;
}