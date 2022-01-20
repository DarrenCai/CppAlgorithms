/**
 * UVa11671
 * 矩阵中的符号
 * 差分约束
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 220
struct edge {int u, v, cost;} e[N*N>>1]; int g[N][N>>1], q[N*N*N], cnt[N], vis[N], c[N], d[N], cc, n; char s[N];

void addEdge(int u, int v, int cost) {
    e[cc].u = u; e[cc].v = v; e[cc].cost = cost; g[u][cnt[u]++] = cc++;
}

bool spfa() {
    int head = 0, tail = 0;
    for (int i=0; i<n; ++i) q[tail++] = i, vis[i] = 1, d[i] = 0, c[i] = 0;
    while (head < tail) {
        int u = q[head++]; vis[u] = 0;
        for (int i=0; i<cnt[u]; ++i) {
            edge& ee = e[g[u][i]];
            if (d[ee.v] > d[u] + ee.cost) {
                d[ee.v] = d[u] + ee.cost;
                if (!vis[ee.v]) {
                    vis[ee.v] = 1; q[tail++] = ee.v;
                    if (++c[ee.v] > n) return false;
                }
            }
        }
    }
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int kase = 0;
    while (cin>>n && n>0) {
        memset(cnt, cc = 0, sizeof(cnt));
        for (int i=0; i<n; ++i) {
            cin >> s;
            for (int j=0; j<n; ++j) {
                if (s[j] == '+') addEdge(j+n, i, -1);
                else if (s[j] == '-') addEdge(i, j+n, -1);
                else addEdge(i, j+n, 0), addEdge(j+n, i, 0);
            }
        }
        n <<= 1;
        cout << "Case " << ++kase << ": ";
        if (spfa()) {
            sort(d, d+n);
            int ans = 0, h = (n>>1)-1;
            for (int i=0; i<n; ++i) ans += abs(d[i]-d[h]);
            cout << ans << endl;
        } else cout << -1 << endl;
    }
    return 0;
}