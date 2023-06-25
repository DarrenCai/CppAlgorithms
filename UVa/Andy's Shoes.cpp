/**
 * UVa11330
 * 安迪的鞋架
 */

#include <iostream>
using namespace std;

#define N 10010
int l[N], r[N], p[N];

int solve() {
    int n, cnt = 0; cin >> n;
    for (int i=0; i<n; ++i) cin >> l[i] >> r[i], p[r[i]] = i;
    for (int i=0; i<n; ++i) if (l[i] != r[i]) {
        int x = p[l[i]], t = r[i];
        p[r[i] = l[i]] = i; p[r[x] = t] = x;
        ++ cnt;
    }
    return cnt;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}