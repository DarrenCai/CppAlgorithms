/**
 * UVa10559
 * 方块消除
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 225
int d[N][N][N], a[N], n;

int dp(int i, int j, int c) {
    int &ref = d[i][j][c];
    if (ref > 0) return ref;
    for (int k=i; k<j; ++k) if (a[k] != a[i]) {
        c += k-i;
        ref = c*c + dp(k, j, 0);
        for (int x=k+1; x<j; ++x) if (a[x] == a[i]) {
            ref = max(ref, dp(k, x, 0) + dp(x, j, c));
            while (x<j && a[x]==a[i]) ++x;
        }
        return ref;
    }
    return ref = (c+j-i)*(c+j-i);
}

int solve() {
    cin >> n;
    for (int i=0; i<n; ++i) cin >> a[i];
    memset(d, 0, sizeof(d));
    return dp(0, n, 0);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    for (short k=1; k<=t; ++k) cout << "Case " << k << ": " << solve() << endl;
    return 0;
}