/**
 * UVa11991
 * 一道简单题
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100005
int a[N], x[N], n, m, k, v;

bool cmp(int i, int j) {
    return a[i] == a[j] ? i < j : a[i] < a[j];
}

bool cmp2(int i, int v) {
    return a[i] < v;
}

int query() {
    int p = lower_bound(x+1, x+1+n, v, cmp2) - x + k - 1;
    return p<=n && a[x[p]]==v ? x[p] : 0;
}

void solve() {
    for (int i=1; i<=n; ++i) cin >> a[i], x[i] = i;
    sort(x+1, x+1+n, cmp);
    while (m--) cin >> k >> v, cout << query() << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) solve();
    return 0;
}