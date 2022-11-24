/**
 * UVa11361
 * 数字和与倍数
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define M 82
int a, b, k, f[10][M][M], p[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

int d(int x) {
    memset(f, 0, sizeof(f)); f[0][0][0] = 1;
    int m = upper_bound(p, p+10, x) - p, ans = 0, s = 0;
    for (int i=1; i<m; ++i) for (int r1=0; r1<M; ++r1) for (int r2=0; r2<M; ++r2) if (f[i-1][r1][r2])
        for (int j=0; j<10; ++j) f[i][(j*p[i-1] + r1) % k][(j + r2) % k] += f[i-1][r1][r2];
    for (int i=1; i<m; ++i) ans += f[i][0][0]-f[i-1][0][0];
    for (int i=x; i; i/=10) s += i%10;
    for (int i=m-1; i>0; --i) {
        int y = x%10; x /= 10; s -= y;
        for (int j=i==m-1 ? y : y-1; j>=0; --j) {
            int r1 = (x*p[m-i] + j*p[m-i-1]) % k, r2 = (s + j) % k;
            ans += f[m-i-1][r1 ? k-r1 : 0][r2 ? k-r2 : 0];
        }
    }
    for (int i=1; i<x; ++i) {
        int r1 = i*p[m-1] % k, r2 = i % k;
        ans += f[m-1][r1 ? k-r1 : 0][r2 ? k-r2 : 0];
    }
    return ans;
}

int solve() {
    cin >> a >> b >> k;
    if (k > M) return 0;
    return d(b) - d(a-1);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}