/**
 * UVa1348/LA3310
 * 程序分析
 * SEERC 2005
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 100010
struct {int c, a, b;} cmds[N]; int g[N][2], c[N], s[N], sn[N], low[N], pre[N], clk, n, p; char t[5];

bool read() {
    n = clk = p = 0;
    while (cin >> t) {
        c[++n] = 0; pre[n] = sn[n] = 0;
        cmds[n].c = !strcasecmp(t, "ifgo") ? 0 : 
            (!strcasecmp(t, "jump") ? 1 : (!strcasecmp(t, "pass") ? 2 : (!strcasecmp(t, "loop") ? 3 : 4)));
        if (cmds[n].c < 2) cin >> cmds[n].a;
        else if (cmds[n].c == 3) {
            cin >> cmds[n].a >> cmds[n].b;
            if (cmds[n].b == 1) cmds[n].c = 2;
        }
        while (cin.get() == ' ');
        if (cin.peek() == '\n') return true;
        if (cin.eof()) return false;
    }
    return true;
}

bool dfs(int u) {
    low[u] = pre[u] = ++clk; s[p++] = u;
    for (int i=0, v; i<c[u]; ++i) {
        if ((v = g[u][i]) == u) return true;
        if (!pre[v]) {
            if (dfs(v)) return true;
            low[u] = min(low[u], low[v]);
        } else if (!sn[v]) low[u] = min(low[u], pre[v]);
    }
    if (low[u] == pre[u]) {
        int cc = 0;
        while (true) {
            ++cc; sn[s[--p]] = 1;
            if (s[p] == u) break;
        }
        return cc > 1;
    }
    return false;
}

bool cycle() {
    for (int i=1; i<=n; ++i) if (cmds[i].c < 4) {
        g[i][c[i]++] = cmds[i].c == 1 ? cmds[i].a : (i<n ? i+1 : 1);
        if (cmds[i].c == 0) g[i][c[i]++] = cmds[i].a;
    }
    return dfs(1);
}

int loop(int i, int j) {
    if (low[i]) return sn[i];
    if (c[i] && c[i] != j) return loop(i, c[i]) + loop(c[i]+1, j);
    int &r = sn[i] = low[i] = 1;
    if (i == j) return c[i] ? r *= cmds[j].b : r;
    r += loop(cmds[i].c==1 ? cmds[i].a : i+1, j);
    if (cmds[i].c == 0) r = max(r, 1 + loop(cmds[i].a, j));
    return c[i] ? r *= cmds[j].b : r;
}

int get(int i) {
    if (cmds[i].c == 4) return 1;
    if (pre[i]) return s[i];
    pre[i] = 1; s[i] = c[i] ? loop(i, c[i]) + get(c[i]+1) : 1 + get(cmds[i].c==1 ? cmds[i].a : i+1);
    if (cmds[i].c == 0) s[i] = max(s[i], 1 + get(cmds[i].a));
    return s[i];
}

void solve() {
    if (!cycle()) {
        for (int i=1; i<=n; ++i) {
            low[i] = pre[i] = c[i] = 0;
            if (cmds[i].c==3) c[cmds[i].a] = i;
        }
        cout << get(1) << endl;
    } else cout << "infinity" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (read()) solve();
    solve();
    return 0;
}