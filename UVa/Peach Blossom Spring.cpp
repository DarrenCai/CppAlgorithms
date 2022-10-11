/**
 * UVa1496/LA5717
 * 桃花源记
 * Beijing 2011
 * 经典问题：图论中的斯坦纳树/森林
 */

#include <iostream>
using namespace std;

#define K 5
#define N 50
#define INF 1100000
int f[N][1<<(K<<1)], d[1<<K][1<<K], w[N][N], c[1<<K]={0}, n, m, k; bool vis[N];

void solve() {
    cin >> n >> m >> k;
    int x = (1<<(k<<1))-1, y = (1<<k)-1;
    for(int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) w[i][j] = INF;
        for (int s=x; s>0; --s) f[i][s] = INF;
    }
    for (int i=0; i<k; ++i) f[i][1<<i] = 0, f[n-k+i][1<<(i+k)] = 0;
    for (int i=1; i<=y; ++i) {
        c[i] = c[(i-1)&i] + 1;
        for (int j=y; j>0; --j) d[i][j] = INF;
    }
    while (m--) {
        int u, v, c; cin >> u >> v >> c;
        --u; --v; w[v][u] = w[u][v] = min(w[u][v], c);
    }
    for (int s=1; s<=x; ++s) {
        for (int i=0; i<n; ++i) {
            vis[i] = false;
            for (int t=(s-1)&s; t>0; t=(t-1)&s) f[i][s] = min(f[i][s], f[i][t]+f[i][s^t]);
        }
        for (int i=1; i<n; ++i) {
            int t = -1, v = INF;
            for (int j=0; j<n; ++j) if (!vis[j] && f[j][s] < v) v = f[t = j][s];
            if (t < 0) break;
            vis[t] = true;
            for (int j=0; j<n; ++j) f[j][s] = min(f[j][s], v+w[t][j]);
        }
        for (int i=0, l, r; i<n; ++i) if (c[l = s&y] == c[r = s>>k]) d[l][r] = min(d[l][r], f[i][s]);
    }
    for (int i=1; i<=y; ++i) for (int j=1; j<=y; ++j) if (c[i] == c[j]) {
        for (int s=(i-1)&i; (s<<1)>i; s=(s-1)&i) for (int t=(j-1)&j; t>0; t=(t-1)&j) if (c[s] == c[t])
            d[i][j] = min(d[i][j], d[s][t]+d[i^s][j^t]);
    }
    d[y][y] < INF ? cout << d[y][y] << endl : cout << "No solution" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}