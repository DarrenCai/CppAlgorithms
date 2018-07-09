/**
 * UVa818
 * 切断圆环链
 */

#include <iostream>
#include <cstring>
using namespace std;

bool g[15][15], visit[15]; unsigned n, c, s, ss;

bool dfs(char cur, char fa) {
    visit[cur] = true;
    for (char i=0; i<n; ++i) {
        if (!g[cur][i] || s&(1<<i) || i==fa) continue;
        if (visit[i]) return true;
        if (dfs(i, cur)) return true;
    }
    return false;
}

bool cycle() {
    for (char i=0; i<n; ++i) {
        if (visit[i] || s&(1<<i)) continue;
        ++ c;
        if (dfs(i, -1)) return true;
    }
    return false;
}

char open(short s) {
    char t = 0;
    while (s) t += s&1, s >>= 1;
    return t;
}

bool ok() {
    for (char i=0; i<n; ++i) {
        if (s&(1<<i)) continue;
        char num = 0;
        for (short j=0; j<n; ++j) {
            if (s&(1<<j)) continue;
            if (g[i][j]) ++num;
        }
        if (num > 2) return false;
    }
    return true;
}

int main()
{
    short t=0;
    while (cin>>n && n) {
	    memset(g, 0, sizeof(g)); short ans = n, a, b; ss = 1<<n;
        while (cin>>a>>b && a!=-1) g[a-1][b-1] = g[b-1][a-1] = true;
        for (s=0; s<ss; ++s) {
            a = open(s); if (a >= ans) continue;
            c = 0; memset(visit, 0, sizeof(visit));
            if (!ok() || cycle()) continue;
            if (c <= a+1) ans = min(a, ans);
        }
        cout << "Set " << ++t << ": Minimum links to open is " << ans << endl;
    }
    return 0;
}