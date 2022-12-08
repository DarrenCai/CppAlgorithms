/**
 * UVa11859
 * 除法游戏
 */

#include <iostream>
using namespace std;

#define N 10010
int c[N] = {0};

int solve() {
    int n, m, ans = 0; cin >> n >> m;
    while (n--) {
        int s = 0;
        for (int i=0, a; i<m; ++i) cin >> a, s += c[a];
        ans ^= s;
    }
    return ans;
}

int dp(int i) {
    for (int j=2; j*j <= i; ++j) if (i%j == 0) return 1 + c[i/j];
    return 1;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<N; ++i) c[i] = dp(i);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case #" << kase << ": " << (solve() ? "YES" : "NO") << endl;
    return 0;
}