/**
 * UVa1665/LA4627
 * 岛屿
 * CERC 2009
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define M 100010
#define N 1000010
int h[N], s[N], f[N], t[M], c[M], q, m, n, x;

bool cmp(int i, int j) {
    return h[i] > h[j] || (h[i]==h[j] && i<j);
};

int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}

void solve() {
    cin >> n >> m; x = m*n;
    for (int i=0; i<x; ++i) cin >> h[i], s[i] = i, f[i] = i;
    cin >> q;
    for (int i=0; i<q; ++i) cin >> t[i];
    sort(s, s+x, cmp);
    int j = 0, k = 0;
    for (int i=q-1, y; i>=0; --i) {
        while (j<x && h[y = s[j]] > t[i]) {
            if (y >= m && h[y-m] > t[i]) {
                int u = find(y), v = find(y-m);
                if (u != v) f[u] = v, --k;
            }
            if (y+m < x && h[y+m] > t[i]) {
                int u = find(y), v = find(y+m);
                if (u != v) f[u] = v, --k;
            }
            if (y%m && h[y-1] > t[i]) {
                int u = find(y), v = find(y-1);
                if (u != v) f[u] = v, --k;
            }
            if ((y+1)%m && h[y+1] > t[i]) {
                int u = find(y), v = find(y+1);
                if (u != v) f[u] = v, --k;
            }
            ++j; ++k;
        }
        c[i] = k;
    }
    for (int i=0; i<q; ++i) cout << c[i] << ' ';
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}