/**
 * UVa562
 * 分硬币
 * 01背包问题
 */

#include <iostream>
using namespace std;

#define max(a, b) (a>b ? a:b)

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        int n, v, w[105], f[30000]={0}, sum = 0; cin >> n;
        for (int i=1; i<=n; ++i) cin >> w[i], sum += w[i];
        v = sum>>1;
        for (int i=1; i<=n; ++i) for (int j=v; j>=w[i]; --j) f[j] = max(f[j-w[i]]+w[i], f[j]);
        cout << sum - (f[v]<<1) << endl;
    }
    return 0;
}