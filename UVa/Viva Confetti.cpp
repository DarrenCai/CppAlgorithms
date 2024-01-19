/**
 * UVa1308/LA2572
 * 圆盘问题
 * Kanazawa 2002
 */

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define N 102
double a[N][N<<1], x[N], y[N], r[N], z = M_PI + M_PI; bool vis[N], esc[N]; int c[N], n;

double check(double x) {
    return x > M_PI ? x-z : (x < -M_PI ? x+z : x);
}

void judge(int i, double a) {
    double px = x[i] + r[i]*cos(a), py = y[i] + r[i]*sin(a);
    for (int j=i+1; j<n; ++j) if (sqrt((px-x[j])*(px-x[j])+(py-y[j])*(py-y[j])) < r[j]) return;
    vis[i] = 1;
    for (int j=i-1; j>=0; --j) if (sqrt((px-x[j])*(px-x[j])+(py-y[j])*(py-y[j])) < r[j]) {
        vis[j] = 1; return;
    }
}

void solve() {
    for (int i=0; i<n; ++i) cin >> x[i] >> y[i] >> r[i], c[i] = vis[i] = esc[i] = 0;
    for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j) {
        double dx = x[i]-x[j], dy = y[i]-y[j], d = sqrt(dx*dx + dy*dy);
        if (d <= max(r[i], r[j])-min(r[i], r[j]) || d >= r[i]+r[j]) {
            if (d <= r[j] - r[i]) esc[i] = 1;
            continue;
        }
        double x = atan2(dy, dx), b = acos((d*d+r[j]*r[j]-r[i]*r[i])/d/r[j]/2),
            y = M_PI - acos((d*d+r[i]*r[i]-r[j]*r[j])/d/r[i]/2);
        a[j][c[j]++] = check(x+b); a[j][c[j]++] = check(x-b);
        a[i][c[i]++] = check(x+y); a[i][c[i]++] = check(x-y);
    }
    for (int i=0; i<n; ++i) {
        if (esc[i]) continue;
        if (c[i]) {
            sort(a[i], a[i]+c[i]);
            judge(i, (a[i][c[i]-1] + a[i][0]) / 2 + M_PI);
            for (int j=c[i]-1; j>0; --j) judge(i, (a[i][j-1] + a[i][j]) / 2);
        } else vis[i] = 1;
    }
    int ans = 0;
    for (int i=0; i<n; ++i) if (vis[i]) ++ans;
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}