/**
 * UVa1427/LA4327
 * 游行
 * Beijing 2008
 */

#include <iostream>
using namespace std;

#define N 110
#define M 10100
int d[2][M], w[N][M], c[M], n, m, k; struct {int i, v;} q[M];

int solve() {
    for (int i=0; i<=n; ++i) {
        d[1][0] = w[i][0] = 0;
        for (int j=1; j<=m; ++j) cin >> w[i][j], w[i][j] += w[i][j-1], d[1][j] = 0;
    }
    int pre = 1, cur = 0;
    for (int i=0; i<=n; ++i) {
        int head = 0, tail = 0, x = 0;
        q[0].i = c[0] = 0; q[0].v = d[pre][0];
        for (int j=1; j<=m; ++j) {
            cin >> c[j];
            if ((c[j] += c[j-1]) > k) continue;
            int v = d[pre][j] + w[i][j];
            while (head<=tail && v>=q[tail].v) --tail;
            q[++tail].i = j; q[tail].v = v; x = j;
        }
        d[cur][0] = q[head].v;
        for (int j=1; j<m; ++j) {
            while (head<=tail && q[head].i<j) ++head;
            while (x<m && c[x+1]-c[j]<=k) {
                ++x;
                int v = d[pre][x] + w[i][x];
                while (head<=tail && v>=q[tail].v) --tail;
                q[++tail].i = x; q[tail].v = v;
            }
            d[cur][j] = q[head].v - w[i][j];
        }
        x = m; q[head = tail = 0].i = m; q[0].v = d[pre][m] - w[i][m];
        for (int j=m-1; j>=0; --j) {
            if (c[m] - c[j] > k) break;
            int v = d[pre][j] - w[i][j];
            while (head<=tail && v>=q[tail].v) --tail;
            q[++tail].i = j; q[tail].v = v; x = j;
        }
        d[cur][m] = q[head].v + w[i][m];
        for (int j=m-1; j>0; --j) {
            while (head<=tail && j<q[head].i) ++head;
            while (x>0 && c[j]-c[x-1] <= k) {
                --x;
                int v = d[pre][x] - w[i][x];
                while (head<=tail && v>=q[tail].v) --tail;
                q[++tail].i = x; q[tail].v = v;
            }
            d[cur][j] = max(d[cur][j], q[head].v + w[i][j]);
        }
        pre ^= 1; cur ^= 1;
    }
    int ans = d[pre][0];
    for (int i=1; i<=m; ++i) ans = max(ans, d[pre][i]);
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n>>m>>k && n) cout << solve() << endl;
    return 0;
}