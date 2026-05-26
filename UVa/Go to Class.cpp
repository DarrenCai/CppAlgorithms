/**
 * UVa1409/LA4019
 * 上学
 * Chengdu 2007
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

#define M 2510
#define N 55
int x[N], y[N], xs, ys, xt, yt, n, m, t, kase = 0; double d[M]; bool f[M];
struct node {
    double d; int u;
    bool operator< (const node& rhs) const {
        return d > rhs.d;
    }
};

bool check(int x1, int y1, int x2, int y2) {
    int k = lower_bound(x, x+m, max(x1, x2)) - x;
    if (k < m && ((x1==x2 && x[k]==x1) || (k&1 && k == upper_bound(x, x+m, min(x1, x2)) - x))) return true;
    k = lower_bound(y, y+n, max(y1, y2)) - y;
    if (k < n && ((y1==y2 && y[k]==y1) || (k&1 && k == upper_bound(y, y+n, min(y1, y2)) - y))) return true;
    if (x1 == x2 || y1 == y2) return false;
    if (x1 > x2) swap(x1, x2), swap(y1, y2);
    long long d = x2 - x1;
    k = upper_bound(x, x+m, x1) - x;
    int a = k==0 ? x1 : max(x[k-1],x1), b= k==m ? x2 : x[k];
    if (y1 < y2) {
        for (int i=0; k<=m; a=b, b = ++k>=m ? x2 : min(x[k],x2)) if (k == m || ~k&1) {
            while (d*y[i] <= (a - x1)*(long long)y2 + (x2 - a)*(long long)y1) ++i;
            if (~i&1 || d*y[i] < (b - x1)*(long long)y2 + (x2 - b)*(long long)y1) return false;
        }
    } else for (int i=n-1; k<=m; a=b, b = ++k>=m ? x2 : min(x[k],x2)) if (k == m || ~k&1) {
        while (d*y[i] >= (a - x1)*(long long)y2 + (x2 - a)*(long long)y1) --i;
        if (i&1 || d*y[i] > (b - x1)*(long long)y2 + (x2 - b)*(long long)y1) return false;
    }
    return true;
}

double dis(int x1, int y1, int x2, int y2) {
    double dx = x1-x2, dy = y1-y2;
    return sqrt(dx*dx+dy*dy);
}

double solve() {
    cin >> xs >> ys >> xt >> yt; n <<= 1; m <<= 1; t = m*n;
    for (int i=0; i<n; ++i) cin >> y[i];
    for (int i=0; i<m; ++i) cin >> x[i];
    sort(x, x+m); sort(y, y+n);
    if (check(xs, ys, xt, yt)) return dis(xs, ys, xt, yt);
    priority_queue<node> q; d[t] = 1e30; f[t] = false;
    for (int i=0, k=0; i<m; ++i) for (int j=0; j<n; ++j, ++k) {
        if (check(xs, ys, x[i], y[j])) q.push({d[k] = dis(xs, ys, x[i], y[j]), k});
        else d[k] = 1e30;
        f[k] = false;
    }
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (u == t) break;
        if (f[u]) continue;
        f[u] = true;
        int x1 = x[u/n], y1 = y[u%n];
        if (check(x1, y1, xt, yt)) {
            double d1 = d[u] + dis(x1, y1, xt, yt);
            if (d[t] > d1) q.push({d[t] = d1, t});
        }
        for (int i=0, k=0; i<m; ++i) for (int j=0; j<n; ++j, ++k) if (!f[k] && check(x1, y1, x[i], y[j])) {
            double d1 = d[u] + dis(x1, y1, x[i], y[j]);
            if (d[k] > d1) q.push({d[k] = d1, k});
        }
    }
    return d[t];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    while (cin >> n >> m && n) cout << "Case " << ++kase << ": " << solve() << endl;
    return 0;
}