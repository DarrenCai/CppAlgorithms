/**
 * P2053 [SCOI2007] 修车
 */

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#define INF 70000
#define M 10
#define N 61

int w[N][M][N], slack[M][N], lx[N], ly[M][N], p[M][N], m, n; bool s[N], t[M][N];

bool match(int i) {
    s[i] = true;
    for (int j=1; j<=m; ++j) for (int k=1; k<=n; ++k) if (!t[j][k]) {
        int d = lx[i] + ly[j][k] + w[i][j][k];
        if (d == 0) {
            t[j][k] = true;
            if (!p[j][k] || match(p[j][k])) {
                p[j][k] = i;
                return true;
            }
        } else slack[j][k] = min(slack[j][k], d);
    }
    return false;
}

void km() {
    memset(lx, 0, sizeof(lx)); memset(ly, 0, sizeof(ly)); memset(p, 0, sizeof(p));
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) for (int k=1; k<=n; ++k) slack[j][k] = INF;
        while (true) {
            memset(s, 0, sizeof(s)); memset(t, 0, sizeof(t));
            if (match(i)) break;
            int a = INF;
            for (int j=1; j<=m; ++j) for (int k=1; k<=n; ++k) if (!t[j][k]) a = min(a, slack[j][k]);
            for (int j=1; j<=n; ++j) if (s[j]) lx[j] -= a;
            for (int j=1; j<=m; ++j) for (int k=1; k<=n; ++k) t[j][k] ? ly[j][k] += a : slack[j][k] -= a;
        }
    }
}

double solve() {
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) {
        int x; cin >> x;
        for (int k=1; k<=n; ++k) w[i][j][k] = k*x;
    }
    km();
    int cc = 0;
    for (int i=1; i<=m; ++i) for (int j=1; j<=n; ++j) if (p[i][j]) cc += w[p[i][j]][i][j];
    return cc / double(n);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(2);
    while (cin >> m >> n) cout << solve() << endl;
    return 0;
}