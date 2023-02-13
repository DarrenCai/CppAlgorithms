/**
 * UVa1430/LA4352
 * 二进制整数
 * Hangzhou 2008
 */

#include <iostream>
using namespace std;

#define K 21
#define M 10007
#define N 41
int f[K][N][N] = {0}, n, k, kase = 0; char s1[N], s2[N];

int pow_mod(int a, int n) {
    int ans = 1;
    while (n) {
        if (n & 1) ans = ans*a % M;
        a = a*a % M;
        n >>= 1;
    }
    return ans;
}

int solve() {
    cin >> s1 >> s2;
    int c = 0;
    for (int i=0; i<n; ++i) if (s1[i] != s2[i]) ++c;
    return f[k][c][n];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int n=0; n<N; ++n) f[0][0][n] = 1, f[1][3][n] = n>2;
    for (int k=2; k<K; ++k) {
        int inv = pow_mod(k, M-2);
        for (int c = min(3*k, N-1); c>=0; --c) {
            if ((3*k-c) & 1) continue;
            for (int n=c; n<N; ++n) {
                int r = 0;
                if (c > 2) r += c*(c-1)*(c-2)/6 * f[k-1][c-3][n] % M;
                if (c > 0) r += c*(c-1)/2*(n-c) * f[k-1][c-1][n] % M;
                if (c < n) r += c*(n-c)*(n-c-1)/2 * f[k-1][c+1][n] % M;
                if (c+2 < n) r += (n-c)*(n-c-1)*(n-c-2)/6 * f[k-1][c+3][n] % M;
                r -= (n*(n-1)*(n-2)/6 - (k-2)) * f[k-2][c][n] % M;
                f[k][c][n] = (r * inv % M + M) % M;
            }
        }
    }
    while (cin>>n>>k && n) cout << "Case #" << ++kase << ": " << solve() << endl;
    return 0;
}