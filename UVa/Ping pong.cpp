/**
 * UVa1428/LA4329
 * 乒乓比赛
 * Beijing 2008
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 100010
#define N 20005
int a[N], c[M], l[N], n, t, x;

int query(int x) {
    int s = 0;
    while (x > 0) s += c[x], x -= x&-x;
    return s;
}

void update(int x) {
    while (x < M) ++c[x], x += x&-x;
}

void solve() {
    cin >> n;
    long long ans = 0;
    memset(c, 0, sizeof(c));
    for (int i=0; i<n; ++i) cin >> a[i], l[i] = query(a[i]), update(a[i]+1);
    memset(c, 0, sizeof(c));
    for (int i=n-1; i>=0; --i) x = query(a[i]), ans += l[i]*(n-1-i-x) + (i-l[i])*x, update(a[i]+1);
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--) solve();
    return 0;
}