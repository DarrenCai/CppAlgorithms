/**
 * UVa11671
 * 矩阵中的符号
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 202
struct {int v, w;} g[N][N>>1]; int c[N], d[N], f[N], cnt[N], q[N*N], n, kase = 0;

bool cycle() {
    int head = 0, tail = n;
    for (int i=0; i<n; ++i) cnt[i] = d[i] = 0, f[i] = 1, q[i] = i;
    while (head < tail) {
        int u = q[head++]; f[u] = 0;
        for (int i=0; i<c[u]; ++i) {
            int v = g[u][i].v, d1 = d[u] + g[u][i].w;
            if (d[v] > d1) {
                d[v] = d1;
                if (++cnt[v] >= n) return true;
                if (!f[v]) q[tail++] = v, f[v] = 1;
            }
        }
    }
    return false;
}

int solve() {
    memset(c, 0, sizeof(c));
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) {
        char x; cin >> x;
        if (x == '+') g[j+n][c[j+n]++] = {i, -1};
        else if (x == '-') g[i][c[i]++] = {j+n, -1};
        else g[j+n][c[j+n]++] = {i, 0}, g[i][c[i]++] = {j+n, 0};
    }
    n <<= 1;
    if (cycle()) return -1;
    sort(d, d+n);
    int cc = 0, h = (n>>1)-1;
    for (int i=0; i<n; ++i) cc += abs(d[i]-d[h]);
    return cc;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n > 0) cout << "Case " << ++kase << ": " << solve() << endl;
    return 0;
}