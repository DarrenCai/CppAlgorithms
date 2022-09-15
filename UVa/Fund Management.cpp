/**
 * UVa1412/LA4048
 * 基金管理
 * NEERC 2007
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 102
#define N 9
#define MX 12880    // C(16,8) = 12870
#define X 38263753  // 8*9^7 + 1
char stock[N][N]; int pp[N], id[X], t[MX], a[N], s[N], k[N], kase = 0, cc, m, n, K;
double c; long long p[N][M], d[M][MX]; struct node { int x, i, f; } ans[M][MX];

void expand(int i, int s, int x = 0, int c = 0) {
    if (i >= n) {
        t[cc] = x; id[x] = cc++;
        return;
    }
    expand(i+1, s+c, x);
    if (c<k[i] && s+c<K) expand(i, s, x+pp[i], c+1);
}

void print(int i, const node& t) {
    if (i > 1) print(i-1, ans[i-1][t.x]);
    (t.f ? cout << (t.f<0 ? "SELL " : "BUY ") << stock[t.i] : cout << "HOLD") << endl;
}

void solve() {
    pp[n-1] = 1; for (int i=n-2; i>=0; --i) pp[i] = N*pp[i+1];
    for (int i=0; i<n; ++i) {
        cin >> stock[i] >> s[i] >> k[i];
        for (int j=0; j<m; ++j) {
            double x; cin >> x;
            p[i][j] = 100*x + .5;
        }
    }
    expand(cc = 0, 0);
    memset(d, -1, sizeof(d)); d[0][0] = 100*c + .5;
    for (int i=0; i<m; ++i) for (int j=0; j<cc; ++j) if (d[i][j] >= 0) {
        int cnt = 0;
        for (int s=n-1, x=t[j]; s>=0; --s, x/=N) cnt += (a[s] = x%N);
        if (d[i][j] > d[i+1][j]) d[i+1][j] = d[i][j], ans[i+1][j].x = j, ans[i+1][j].f = 0;
        if (cnt>0) for (int c=0; c<n; ++c) if (a[c] > 0) {
            long long v = d[i][j] + s[c] * p[c][i]; int x = id[t[j] - pp[c]];
            if (v > d[i+1][x]) d[i+1][x] = v, ans[i+1][x].x = j, ans[i+1][x].i = c, ans[i+1][x].f = -1;
        }
        if (cnt<K) for (int c=0; c<n; ++c) if (a[c]<k[c]) {
            long long v = d[i][j] - s[c] * p[c][i];
            if (v < 0) continue;
            int x = id[t[j] + pp[c]];
            if (v > d[i+1][x]) d[i+1][x] = v, ans[i+1][x].x = j, ans[i+1][x].i = c, ans[i+1][x].f = 1;
        }
    }
    if (kase++) cout << endl;
    cout << d[m][0] / 100;
    d[m][0] %= 100;
    cout << (d[m][0]<10 ? ".0" : ".") << d[m][0] << endl;
    print(m, ans[m][0]);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> c >> m >> n >> K) solve();
    return 0;
}