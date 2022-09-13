/**
 * UVa1439/LA4593
 * 独占访问2
 * NEERC 2009
 * 很好的一道题目，可以转换成图的色数问题：对无向图G，把图中的结点染成尽量少的颜色，使得相邻结点颜色不同。
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 20
#define M 200
short e[M][2], a[N], c[N], c1[N], n, ans, cnt; bool g[N][N], v[N];

bool check(short i, short color) {
    for (short j=0; j<n; ++j) if (g[a[i]][a[j]] && c1[a[j]] == color) return false;
    return true;
}

void dfs(short i) {
    if (cnt >= ans) return;
    if (i >= n) {
        ans = cnt; memcpy(c, c1, sizeof(c));
    } else for (short color=1; color <= cnt+1; ++color) {
        if (check(i, color)) {
            c1[a[i]] = color;
            if (color > cnt) {
                ++ cnt;
                dfs(i+1);
                -- cnt;
            } else dfs(i+1);
            c1[a[i]] = 0;
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short m;
    while (cin >> m) {
        n=0; ans=N; cnt=0; memset(c1, 0, sizeof(c1)); memset(g, 0, sizeof(g)); memset(v, 0, sizeof(v));
        for (short i=0; i<m; ++i) {
            char c1, c2; cin >> c1 >> c2; c1 -= 'L'; c2 -= 'L';
            if (!v[c1]) a[n++] = c1, v[c1] = true;
            if (!v[c2]) a[n++] = c2, v[c2] = true;
            g[c1][c2] = g[c2][c1] = true;
            e[i][0] = c1; e[i][1] = c2;
        }
        dfs(0);
        cout << ans-2 << endl;
        for (short i=0; i<m; ++i) {
            char c1 = 'L'+e[i][0], c2 = 'L'+e[i][1]; bool less = c[e[i][0]] < c[e[i][1]];
            cout << (less ? c1 : c2) << ' ' << (less ? c2 : c1) << endl;
        }
    }
    return 0;
}