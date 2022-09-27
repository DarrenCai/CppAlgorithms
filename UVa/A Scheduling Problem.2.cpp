/**
 * UVa1380/LA3683
 * 一个调度问题
 * Asia - Kaohsiung 2006
 */

#include <iostream>
using namespace std;

#define N 205
short t[N][N], d[N][N], c[N], f[N], g[N], k; bool dp[N][N];

void dfs(short u, short fa = 0) {
    short a = 0, b = 0;
    for (short i=0, v; i<c[u]; ++i) if ((v = t[u][i]) != fa) {
        dfs(v, u);
        if (d[u][v] == 1) a = max(int(a), 1+f[v]);
        else if (d[u][v]) b = max(int(b), 1+g[v]);
    }
    f[u] = a; g[u] = b;
    k = max(int(k), a+b);
}

short dfs2(short u, short fa = 0) {
    for (short i=0, v; i<c[u]; ++i) if ((v = t[u][i]) != fa) if (dfs2(v, u) > k) return k+1;
    short r = 1;
    for (short i=0; i<=k; ++i) {
        dp[u][i] = true;
        for (short j=0, v; j<c[u]; ++j) if ((v = t[u][j]) != fa) {
            if (d[u][v] == 1) {
                bool ok = false;
                for (short x=0; x<i; ++x) if (dp[v][x]) {
                    ok = true; break;
                }
                if (!ok) dp[u][i] = false;
            } else if (d[u][v]) {
                bool ok = false;
                for (short x=i+1; x<=k; ++x) if (dp[v][x]) {
                    ok = true; break;
                }
                if (!ok) dp[u][i] = false;
            } else {
                bool ok = false;
                for (short x=0; x<=k; ++x) if (x!=i && dp[v][x]) {
                    ok = true; break;
                }
                if (!ok) dp[u][i] = false;
            }
            if (!dp[u][i]) break;
        }
        if (dp[u][i]) r = 0;
    }
    return k+r;
}

bool solve() {
    int u, v; cin >> u;
    if (!u) return false;
    for (short i=1; i<N; ++i) c[i] = 0;
    while (u) {
        while (cin>>v && v) {
            char h = cin.get();
            t[u][c[u]++] = v; d[u][v] = h=='u' ? 1 : (h=='d' ? -1 : 0);
            t[v][c[v]++] = u; d[v][u] = -d[u][v];
        }
        cin >> u;
    }
    k = 0;
    dfs(1);
    cout << dfs2(1)+1 << endl;
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (solve());
    return 0;
}