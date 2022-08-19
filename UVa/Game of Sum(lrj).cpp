/**
 * UVa10891
 * Sum游戏
 */

#include <iostream>
using namespace std;

#define N 110
int a[N], n; long long d[N][N], f[N][N], g[N][N], s[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    s[0] = 0;
    while (cin>>n && n) {
        for (int i=1; i<=n; ++i) cin >> a[i], s[i] = s[i-1] + a[i];
        for (int l=1; l<=n; ++l) for (int i=n-l+1; i>0; --i) {
            int j = i+l-1; long long v = s[j] - s[i-1], &ref = d[i][j] = v;
            if (l > 1) ref = max(ref, v - min(f[i+1][j], g[i][j-1]));
            l>1 ? f[i][j] = min(ref, f[i+1][j]), g[i][j] = min(ref, g[i][j-1]) : f[i][i] = g[i][i] = ref;
        }
        cout << 2*d[1][n] - s[n] << endl;
    }
    return 0;
}