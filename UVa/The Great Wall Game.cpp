/**
 * UVa1045/LA3276
 * 长城游戏
 * World Finals 2005
 */

#include <iostream>
using namespace std;

#define INF 300
#define N 17
int w[N][N], slack[N], lx[N], ly[N], p[N], r[N], c[N], n, kase = 0; bool s[N], t[N];

bool match(int i) {
    s[i] = true;
    for (int j=1; j<=n; ++j) if (!t[j]) {
        int d = lx[i] + ly[j] + w[i][j];
        if (d == 0) {
            t[j] = true;
            if (!p[j] || match(p[j])) {
                p[j] = i;
                return true;
            }
        } else slack[j] = min(slack[j], d);
    }
    return false;
}

int km() {
    for (int i=1; i<=n; ++i) p[i] = lx[i] = ly[i] = 0;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) slack[j] = INF;
        while (true) {
            for (int j=1; j<=n; ++j) s[j] = t[j] = false;
            if (match(i)) break;
            int a = INF;
            for (int j=1; j<=n; ++j) if (!t[j]) a = min(a, slack[j]);
            for (int j=1; j<=n; ++j) {
                if (s[j]) lx[j] -= a;
                t[j] ? ly[j] += a : slack[j] -= a;
            }
        }
    }
    int cc = 0;
    for (int i=1; i<=n; ++i) cc += w[p[i]][i];
    return cc;
}

int solve () {
    for (int i=1; i<=n; ++i) cin >> r[i] >> c[i];
    if (n == 1) return 0;
    int ans = INF;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) for (int k=1; k<=n; ++k) w[j][k] = abs(r[k]-i) + abs(c[k]-j);
        ans = min(ans, km());
        for (int j=1; j<=n; ++j) for (int k=1; k<=n; ++k) w[j][k] = abs(r[k]-j) + abs(c[k]-i);
        ans = min(ans, km());
    }
    for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) w[i][j] = abs(r[j]-i) + abs(c[j]-i);
    ans = min(ans, km());
    for (int i=1; i<=n; ++i) for (int j=1, k=n+1-i; j<=n; ++j) w[i][j] = abs(r[j]-i) + abs(c[j]-k);
    ans = min(ans, km());
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) cout << "Board " << ++kase << ": " << solve() << " moves required." << endl << endl;
    return 0;
}