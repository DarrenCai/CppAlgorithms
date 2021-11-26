/**
 * UVa1664
 * 占领新区域
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 200100
int u[N], v[N], c[N], e[N], p[N], cnt[N], n; long long w[N];

bool cmp(int a, int b) {
    return c[a] > c[b];
}

int find(int x) {
    return p[x]==x ? x : p[x] = find(p[x]);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        long long ans = 0;
        for (int i=1; i<=n; ++i) cnt[p[i] = i] = 1, w[i] = 0;
        for (int i=1; i<n; ++i) cin >> u[i] >> v[i] >> c[i], e[i] = i;
        sort(e+1, e+n, cmp);
        for (int i=1; i<n; ++i) {
            int x = find(u[e[i]]), y = find(v[e[i]]);
            long long a = w[x] + (long long)cnt[y]*c[e[i]], b = w[y] + (long long)cnt[x]*c[e[i]];
            a > b ? (cnt[p[y] = x] += cnt[y], ans = w[x] = a) : (cnt[p[x] = y] += cnt[x], ans = w[y] = b);
        }
        cout << ans << endl;
    }
    return 0;
}