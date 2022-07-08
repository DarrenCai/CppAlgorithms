/**
 * LA5842/UVa1508
 * Regionals 2011 >> Asia - Daejeon
 */

#include <iostream>
using namespace std;

#define N 10100
#define M 5
int r[N][M], a[M], ans, n, k;

void dfs(int curr = 0) {
    if (curr == M) {
        int m[M] = {0}, s = 0;
        for (int i=0; i<n; ++i) {
            int t[M] = {0};
            for (int j=0; j<M; ++j) t[a[j]] += r[i][j];
            for (int j=0; j<k; ++j) m[j] = max(m[j], t[j]);
        }
        for (int i=0; i<k; ++i) s += m[i];
        ans = max(ans, s);
    } else for (int i=0; i < k; ++i) {
        a[curr] = i;
        dfs(curr+1);
    }
}

int solve() {
    cin >> n >> k;
    for (int i=0; i<n; ++i) for (int j=0; j<M; ++j) cin >> r[i][j];
    ans = 0;
    if (k >= M) {
        for (int i=0; i<M; ++i) {
            int m = 0;
            for (int j=0; j<n; ++j) m = max(m, r[j][i]);
            ans += m;
        }
    } else dfs();
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}