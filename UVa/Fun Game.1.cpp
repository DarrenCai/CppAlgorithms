/**
 * UVa1204/LA3136
 * 有趣的游戏
 * Beijing 2004
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define M 105
#define N 18
char s[N][M], r[N][M]; int c[N][2][N][2], d[1<<N][N][2], a[N], z[N], n, t;

bool cmp(int i, int j) {
    return z[i] > z[j];
}

bool check(int i) {
    for (int j=0; j<t; ++j) for (int k=z[a[j]]-z[i]; k>=0; --k)
        if (!strncmp(s[i], s[a[j]]+k, z[i]) || !strncmp(s[i], r[a[j]]+k, z[i])) return false;
    return true;
}

int lap(int i, int x, int j, int y) {
    const char (&p)[M] = x ? r[i] : s[i], (&q)[M] = y ? r[j] : s[j];
    for (int k=z[j]-1; k>0; --k) if (!strncmp(p+z[i]-k, q, k)) return k;
    return 0;
}

void solve() {
    for (int i=0; i<n; ++i) {
        cin >> s[i]; z[i] = strlen(s[i]); a[i] = i;
        for (int j=z[i]-1, k=j; j>=0; --j) r[i][j] = s[i][k-j];
    }
    sort(a, a+n, cmp);
    for (int i = t = 1; i<n; ++i) if (check(a[i])) a[t++] = a[i];
    for (int i=0; i<t; ++i) for (int j=i+1; j<t; ++j)
        c[j][1][i][1] = c[i][0][j][0] = lap(a[i], 0, a[j], 0),
        c[j][0][i][1] = c[i][0][j][1] = lap(a[i], 0, a[j], 1),
        c[j][1][i][0] = c[i][1][j][0] = lap(a[i], 1, a[j], 0),
        c[j][0][i][0] = c[i][1][j][1] = lap(a[i], 1, a[j], 1);
    c[0][0][0][0] = lap(0, 0, 0, 0);
    n = (1<<t) - 1; memset(d, 0, sizeof(d)); d[1][0][0] = z[a[0]];
    for (int s=1; s<=n; ++s) for (int i=0; i<t; ++i) if (s&(1<<i)) for (int j=0; j<2; ++j) if (d[s][i][j])
        for (int k=1; k<t; ++k) if (~s&(1<<k)) for (int l=0; l<2; ++l) {
            int &r = d[s | (1<<k)][k][l], x = d[s][i][j] + z[a[k]] - c[i][j][k][l];
            r = r ? min(r, x) : x;
        }
    int ans = M*t;
    for (int i=0; i<t; ++i) for (int j=0; j<2; ++j) if (d[n][i][j]) ans = min(ans, d[n][i][j]-c[i][j][0][0]);
    cout << max(ans, 2) << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) solve();
    return 0;
}