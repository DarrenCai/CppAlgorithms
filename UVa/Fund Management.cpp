/**
 * UVa1412
 * 基金管理
 */

#include <iostream>
#include <cstring>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define M 102
#define N 10
#define MX 13000    // c(16,8) < 13000
#define X 38263753  // 8*9^7 + 1
long long c, p[M][N], dp[M][MX]; short t=0, m, n, ks, k[N], ans[M][MX]; char name[N][7];
int info[MX][N], id[X], d[] = {1, 9, 81, 729, 6561, 59049, 531441, 4782969}, s[N];

void print(short day, short id) {
    if (day < 1) return;
    int preId = ans[day][id];
    print(day-1, preId);
    if (preId == id) {
        cout << "HOLD" << endl;
    } else for (short i=0; i<n; ++i) if (info[preId][i] != info[id][i]) {
        cout << (info[preId][i] < info[id][i] ? "BUY " : "SELL ") << name[i] << endl;
        return;
    }
}

void bfs() {
    memset(dp, -1, sizeof(dp)); dp[0][0] = c;
    for (short i=1; i<m; ++i) {
        int mx = min(ks*d[n-1]+1, (k[n-1]+1)*d[n-1]);
        for (short j=0; j<t && info[j][9] < mx; ++j) if (dp[i-1][j] >= 0) {
            if (info[j][8] <= m-i && dp[i-1][j] > dp[i][j]) dp[i][j] = dp[i-1][j], ans[i][j] = j;
            long long cc; int jj;
            for (short k=0; k<n; ++k) {
                if (info[j][k] > 0 && (cc = dp[i-1][j] + p[i][k]*s[k]) > dp[i][jj = id[info[j][9]-d[k]]])
                    dp[i][jj] = cc, ans[i][jj] = j;
                if (info[j][k] < ::k[k] && info[j][8] < ks && info[j][8] < m-i
                    && (cc = dp[i-1][j] - p[i][k]*s[k]) > dp[i][jj = id[info[j][9]+d[k]]])
                    dp[i][jj] = cc, ans[i][jj] = j;
            }
        }
    }
    long long max = dp[m-1][0], cc; ans[m][0] = 0;
    for (short j=1; j<t && info[j][9] <= d[n-1]; ++j) if (dp[m-1][j] >= 0 && info[j][8] == 1)
        for (short k=0; k<n; ++k) if (info[j][k] == 1) {
            if ((cc = dp[m-1][j] + p[m][k]*s[k]) > max) max = cc, ans[m][0] = j;
            break;
        }
    cc = max%100;
    cout << max/100 << (cc < 10 ? ".0" : ".") << cc << endl;
    print(m, 0);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int kase = 0; short b[N]; double cc;
    for (int i=0; i<X; ++i) {
        int sum = 0, v = i;
        for (int j=0; j<8; ++j) b[j] = v%9, sum += b[j], v /= 9;
        if (sum <= 8) {
            for (int j=0; j<8; ++j) info[t][j] = b[j];
            info[t][8] = sum; info[t][9] = i; id[i] = t++;
        }
    }
    while (cin >> cc >> m >> n >> ks) {
        if (kase++ > 0) cout << endl;
        c = cc * 100 + .5;
        for (short i=0; i<n; ++i) {
            cin >> name[i] >> s[i] >> k[i];
            for (short j=1; j<=m; ++j) cin >> cc, p[j][i] = cc * 100 + .5;
        }
        bfs();
    }
    return 0;
}