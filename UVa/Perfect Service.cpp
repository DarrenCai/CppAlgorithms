/**
 * UVa1218
 * 完美的服务
 */

#include <iostream>
#include <vector>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define N 10010
vector<short> e[N], g[N]; bool visit[N];
short n, d00[N], d01[N], d1[N];

void create(short i = 1) {
    visit[i] = true;
    for (short j=e[i].size()-1; j>=0; --j) if (!visit[e[i][j]]) {
        g[i].push_back(e[i][j]);
        create(e[i][j]);
    }
}

void dp(short i = 1) {
    if (g[i].size() == 0) {
        d00[i] = n; d01[i] = 0; d1[i] = 1;
        return;
    }
    for (short j=g[i].size()-1; j>=0; --j) dp(g[i][j]);
    int v = 0;
    for (short j=g[i].size()-1; j>=0; --j)  v += d00[g[i][j]];
    d01[i] = v;
    if (d01[i] > n) d01[i] = n;
    d00[i] = n;
    for (short j=g[i].size()-1; j>=0; --j) {
        v = d1[g[i][j]];
        for (short k=g[i].size()-1; k>=0; --k) if (j != k) {
            if (g[g[i][k]].size() == 0) {
                v = n; break;
            }
            v += d00[g[i][k]];
        }
        if (v < d00[i]) d00[i] = v;
    }
    if (d00[i] > n) d00[i] = n;
    d1[i] = 1;
    for (short j=g[i].size()-1; j>=0; --j) d1[i] += min(d01[g[i][j]], d1[g[i][j]]);
    if (d1[i] > n) d1[i] = n;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (true) {
        cin >> n;
        for (short i=1; i<=n; ++i) e[i].clear(), g[i].clear(), visit[i] = false;
        for (short i=1; i<n; ++i) {
            short u, v; cin >> u >> v;
            e[u].push_back(v); e[v].push_back(u);
        }
        create();
        dp();
        cout << min(d00[1], d1[1]) << endl;
        if (cin >> n && n==-1) return 0;
    }
    return 0;
}