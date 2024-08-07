/**
 * P3705 [SDOI2017] 新生舞会
 */

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#define INF 1e30
#define N 102
double slack[N], lx[N], ly[N], m; int a[N][N], b[N][N], pre[N], p[N], vis[N], n, clk;

void bfs(int u) {
    for (int i=1; i<=n; ++i) pre[i] = 0, slack[i] = INF;
    int y = 0, yy = 0; p[0] = u;
    do {
        double d = INF; int x = p[y]; vis[y] = clk;
        for (int i=1; i<=n; ++i) if (vis[i] != clk) {
            double w = lx[x] + ly[i] - a[x][i] + m*b[x][i];
            if (slack[i] > w) slack[i] = w, pre[i] = y;
            if (slack[i] < d) d = slack[i], yy = i;
        }
        for (int i=0; i<=n; ++i) vis[i] == clk ? (lx[p[i]]-=d, ly[i] += d) : slack[i] -= d;
        y = yy;
    } while (p[y]);
    while (y) p[y] = p[pre[y]], y = pre[y];
}

double km() {
    lx[0] = ly[0] = 0.; vis[0] = 0;
    for (int i=1; i<=n; ++i) {
        p[i] = 0; lx[i] = -INF; ly[i] = 0.; vis[i] = 0;
        for (int j=1; j<=n; ++j) lx[i] = max(lx[i], a[i][j] - m*b[i][j]);
    }
    for (int i=1; i<=n; ++i) bfs(clk = i);
    double cc = 0.;
    for (int i=1; i<=n; ++i) cc += a[p[i]][i] - m*b[p[i]][i];
    return cc;
}

double solve() {
    for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) cin >> a[i][j];
    for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) cin >> b[i][j];
    double l = 0., r = 1e4, eps = 1e-8;
    while (l+eps <= r) {
        m = .5*(l+r);
        km() < 0. ? r = m-eps : l = m+eps; 
    }
    return r;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(6);
    while (cin >> n) cout << solve() << endl;
    return 0;
}