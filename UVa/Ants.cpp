/**
 * UVa1411/LA4043
 * 蚂蚁
 * NEERC 2008
 */

#include <iostream>
#include <cmath>
using namespace std;

#define INF 1e30
#define eps 1e-9
#define N 102
double w[N][N], slack[N], lx[N], ly[N]; int p[N], x[N], y[N], n, kase=0; bool s[N], t[N];

bool match(int i) {
    s[i] = true;
    for (int j=1; j<=n; ++j) if (!t[j]) {
        double d = lx[i] + ly[j] - w[i][j];
        if (abs(d) < eps) {
            t[j] = true;
            if (!p[j] || match(p[j])) {
                p[j] = i;
                return true;
            }
        } else slack[j] = min(slack[j], d);
    }
    return false;
}

void km() {
    for (int i=1; i<=n; ++i) {
        p[i] = 0; lx[i] = 0.; ly[i] = 0.;
        for (int j=1; j<=n; ++j) lx[i] = max(lx[i], w[i][j]);
    }
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) slack[j] = INF;
        while (true) {
            for (int j=1; j<=n; ++j) s[j] = t[j] = false;
            if (match(i)) break;
            double a = INF;
            for (int j=1; j<=n; ++j) if (!t[j]) a = min(a, slack[j]);
            for (int j=1; j<=n; ++j) {
                if (s[j]) lx[j] -= a;
                t[j] ? ly[j] += a : slack[j] -= a;
            }
        }
    }
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