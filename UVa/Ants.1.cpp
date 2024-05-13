/**
 * UVa1411/LA4043
 * 蚂蚁
 * NEERC 2008
 */

#include <iostream>
#include <cmath>
using namespace std;

#define INF 1e30
#define N 102
double w[N][N], slack[N], lx[N], ly[N]; int pre[N], p[N], vis[N], x[N], y[N], n, clk, kase=0; bool s[N], t[N];

void bfs(int u) {
    for (int i=1; i<=n; ++i) pre[i] = 0, slack[i] = INF;
    int y = 0, yy = 0; p[0] = u;
    do {
        double d = INF; int x = p[y]; vis[y] = clk;
        for (int i=1; i<=n; ++i) if (vis[i] != clk) {
            if (slack[i] > lx[x]+ly[i]-w[x][i]) slack[i] = lx[x]+ly[i]-w[x][i], pre[i] = y;
            if (slack[i] < d) d = slack[i], yy = i;
        }
        for (int i=0; i<=n; ++i) vis[i] == clk ? (lx[p[i]]-=d, ly[i] += d) : slack[i] -= d;
        y = yy;
    } while (p[y]);
    while (y) p[y] = p[pre[y]], y = pre[y];
}

void km() {
    lx[0] = ly[0] = 0.; vis[0] = 0;
    for (int i=1; i<=n; ++i) {
        p[i] = 0; lx[i] = -INF; ly[i] = 0.; vis[i] = 0;
        for (int j=1; j<=n; ++j) lx[i] = max(lx[i], w[i][j]);
    }
    for (int i=1; i<=n; ++i) bfs(clk = i);
}

void solve() {
    for (int i=1; i<=n; ++i) cin >> x[i] >> y[i];
    for (int i=1; i<=n; ++i) {
        int a, b; cin >> a >> b;
        for (int j=1; j<=n; ++j) w[i][j] = -sqrt((x[j]-a)*(x[j]-a) + (y[j]-b)*(y[j]-b));
    }
    km();
    if (kase++) cout << endl;
    for (int i=1; i<=n; ++i) cout << p[i] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) solve();
    return 0;
}