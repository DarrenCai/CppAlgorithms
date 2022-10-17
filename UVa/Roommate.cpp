/**
 * UVa1370/LA3605
 * 室友
 * Asia Seoul 2006
 */

#include <iostream>
#include <cstring>
using namespace std;

#define INF 70000
#define M 320
#define N 110

int d[M][M][N<<1], sa[M], sb[M], wa[M], wb[M], ta[N>>1], tb[N>>1], a, b, n;

int dp(int i, int j, int k) {
    int &r = d[i][j][k];
    if (r < INF) return r;
    if (i>=a && j>=b) return r = k<N ? k : k-N;
    if (k == N) {
        if (i >= a) return r = wb[b] - wb[j];
        if (j >= b) return r = wa[a] - wa[i];
        return r = min(dp(i, j+1, tb[sb[j+1]]), dp(i+1, j, N+ta[sa[i+1]]));
    }
    if (k < N) {
        r = k + dp(i, j, N);
        if (i<a && sa[i+1] != sb[j]) {
            int t = ta[sa[i+1]];
            r = min(r, k>t ? t + dp(i+1, j, k-t) : k + dp(i+1, j, N+t-k));
        }
    } else {
        k -= N;
        r = k + dp(i, j, N);
        if (j<b && sb[j+1] != sa[i]) {
            int t = tb[sb[j+1]];
            r = min(r, k<t ? k + dp(i, j+1, t-k) : t + dp(i, j+1, N+k-t));
        }
    }
    return r;
}

int solve() {
    cin >> n;
    for (int i=1; i<=n; ++i) cin >> ta[i];
    for (int i=1; i<=n; ++i) cin >> tb[i];
    cin >> a >> b;
    for (int i=1; i<=a; ++i) cin >> sa[i], wa[i] = wa[i-1] + ta[sa[i]];
    for (int i=1; i<=b; ++i) cin >> sb[i], wb[i] = wb[i-1] + tb[sb[i]];
    memset(d, 1, sizeof(d));
    return dp(0, 0, N);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    wa[0] = wb[0] = 0;
    short t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}