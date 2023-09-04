/**
 * UVa1332/LA3139
 * 怪盗基德
 * Beijing 2004
 */

#include <iostream>
#include <numeric>
using namespace std;

#define K 22
int m[K][K], a[K][K], gm[K][K], g[K][K], ym[K][K], y[K][K], x[K], b, c, k, n, p, ans;

void dfs(int p, int cnt = 0) {
    if (p < 0) {
        ans = min(ans, cnt);
        return;
    }
    for (x[p]=0; x[p]<n; ++x[p]) if (cnt+x[p] < ans &&  a[p][p]*x[p]%n == a[p][k]) {
        int i = -1;
        while (++i < p) {
            y[i][p] = a[i][k];
            a[i][k] = (a[i][k] - a[i][p]*x[p]%n + n) % n;
            if ((p==0 && a[i][k]) || (p && a[i][k] % g[i][p-1])) {
                break;
            }
        }
        if (i == p) {
            int j = -1;
            while (++j < k) {
                ym[j][p] = m[j][k];
                m[j][k] = (m[j][k] - m[j][p]*x[p]%n + n) % n;
                if ((p==0 && m[j][k]) || (p && m[j][k] % gm[j][p-1])) break;
            }
            if (j == k) --j, dfs(p-1, cnt + x[p]);
            while (j>=0) m[j][k] = ym[j][p], --j;
            --i;
        }
        while (i>=0) a[i][k] = y[i][p], --i;
    }
}

void solve() {
    for (int i=0; i<k; ++i) {
        cin >> a[i][k]; m[i][k] = a[i][k] = a[i][k]==1 ? 0 : n+1-a[i][k];
        for (int j=0; j<k; ++j) m[i][j] = a[i][j] = 0;
    }
    for (int i=0; i<k; ++i) {
        cin >> p;
        while (p--) cin >> c >> b, m[c-1][i] = a[c-1][i] = b;
    }
    for (int i=0; i<k; ++i) {
        gm[i][0] = gcd(n, m[i][0]);
        for (int j=1; j<k; ++j) gm[i][j] = gcd(gm[i][j-1], m[i][j]);
        if (a[i][k] % gm[i][k-1]) {
            cout << "No solution" << endl;
            return;
        }
    }
    for (int i=0; i<k; ++i) {
        for (int j=i; j<k; ++j) if (a[j][i]) {
            if (j > i) for (int x=i, t; x<=k; ++x) t = a[i][x], a[i][x] = a[j][x], a[j][x] = t;
            for (j=i+1; j<k; ++j) while (a[j][i]) {
                int x = a[i][i] / a[j][i];
                for (int y=i; y<=k; ++y) {
                    int t = a[j][y];
                    a[j][y] = (a[i][y] - x*a[j][y]%n + n) % n;
                    a[i][y] = t;
                }
            }
            break;
        }
        g[i][i] = gcd(n, a[i][i]);
        for (int j=i+1; j<k; ++j) g[i][j] = gcd(g[i][j-1], a[i][j]);
        if (a[i][k] % g[i][k-1]) {
            cout << "No solution" << endl;
            return;
        }
    }
    ans = k*n;
    dfs(k-1);
    if (ans == k*n) {
        cout << "No solution" << endl;
        return;
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>k>>n && k) solve();
    return 0;
}