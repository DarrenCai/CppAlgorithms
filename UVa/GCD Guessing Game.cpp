/**
 * UVa1521/LA5916
 * 最大公约数版猜字游戏
 * NEERC 2011
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 10005
#define M 101
int prim[N], t = 0, n; bool f[N] = {false};

void solve() {
    int ans = 0, l = 0, r = upper_bound(prim, prim+t, n) - prim - 1;
    while (l <= r) {
        if (prim[l] * prim[r] <= n) ++l;
        ++ans; --r;
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    for (int i=2; i<M; ++i) if (!f[i]) for (int j=i*i; j<N; j+=i) f[j] = true;
    for (int i=2; i<N; ++i) if (!f[i]) prim[t++] = i;
    while (cin >> n) solve();
    return 0;
}