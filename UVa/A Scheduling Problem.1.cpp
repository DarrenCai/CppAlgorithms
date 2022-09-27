/**
 * UVa1380/LA3683
 * 一个调度问题
 * Asia - Kaohsiung 2006
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 205
short t[N][N], d[N][N], c[N], f[N], g[N], p[N], k;

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

bool cmpf(short i, short j) {
    return f[i] < f[j];
}

bool cmpg(short i, short j) {
    return g[i] < g[j];
}

short dfs2(short u, short fa = 0) {
    if (c[u]) {
        for (short i=0, v; i<c[u]; ++i) if ((v = t[u][i]) != fa) if (dfs2(v, u) > k) return k+1;
        short a = 0, b = 0, cc = 0;
        for (short i=0, v; i<c[u]; ++i) {
            if ((v = t[u][i]) == fa) continue;
            p[cc++] = v;
            if (d[u][v] == 1) a = max(int(a), 1+f[v]);
            else if (d[u][v]) b = max(int(b), 1+g[v]);
        }
        if (a+b > k) return k+1;
        short ff = a, gg = b;
        for (short i=0, v; i<cc; ++i) if (!d[u][v = p[i]]) {
            if (f[v] >= a) gg = max(int(gg), 1+g[v]);
            if (g[v] >= b) ff = max(int(ff), 1+f[v]);
        }
        f[u] = a+gg <= k ? a : k+1;
        g[u] = b+ff <= k ? b : k+1;
        if (f[u] > k) {
            sort(p, p+cc, cmpf);
            for (short i=0, v; i<cc; ++i) if (!d[u][v = p[i]] && f[v]>=a) {
                ff = 1+f[v]; gg = b;
                for (short j=i+1; j<cc; ++j) if (!d[u][v = p[j]]) gg = max(int(gg), 1+g[v]);
                if (ff+gg <= k) {
                    f[u] = ff; break;
                }
            }
            if (f[u] > k) return k+1;
        }
        if (g[u] > k) {
            sort(p, p+cc, cmpg);
            for (short i=0, v; i<cc; ++i) if (!d[u][v = p[i]] && g[v]>=b) {
                ff = a; gg = 1+g[v];
                for (short j=i+1; j<cc; ++j) if (!d[u][v = p[j]]) ff = max(int(ff), 1+f[v]);
                if (ff+gg <= k) {
                    g[u] = gg; break;
                }
            }
            if (g[u] > k) return k+1;
        }
    } else f[u] = g[u] = 0;
    return k;
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