/**
 * UVa11139
 * 数四边形
 * 用到的数学知识：皮克定理 Pick's theorem（https://en.wikipedia.org/wiki/Pick%27s_theorem）
 */

#include <iostream>
using namespace std;

#define N 123
int f[N][N][N], g[N][N], n; long long c[N][N];

int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else if (b & 1) return gcd(a >> 1, b);
    return gcd(a >> 1, b >> 1) << 1;
}

void init() {
    for (int i=0; i<N; ++i) for (int j=i; j<N; ++j) g[i][j] = g[j][i] = gcd(i, j);
    for (int i=0; i<N; ++i) for (int j=0; j<N; ++j) {
        f[i][j][0] = 0;
        for (int k=1; k<N; ++k) f[i][j][k] = f[i][j][k-1] + (i ? (k*j%i ? k*j/i : k*j/i-1) : 0);
    }
    for (int x=1; x<N; ++x) for (int y=x; y<N; ++y) {
        long long t = (x+1)*(y+1) - g[x][y] - 1;
        long long cc = t*t/2-1 + (x-1)*(x-2) + (y-1)*(y-2) + (x-1)*(y-1)*(6*(x+y) - 8) + (x-1)*(x-1)*(y-1)*(y-1);
        for (int x1=1; x1<=x; ++x1) {
            int y1 = y*x1; y1 = y1%x ? y1/x : y1/x-1;
            while (y1 >= 0) {
                cc += 2*(f[y1][x1][y1] - f[y-y1][x-x1][y1] - g[y-y1][x-x1]*y1/(y-y1));
                cc += 2*(f[x-x1][y-y1][x-x1] - f[x1][y1][x-x1] - g[x1][y1]*(x-x1)/x1);
                cc += 6*(x1*y-x*y1 + 2 - g[x1][y1] - g[x-x1][y-y1] - g[x][y]);
                --y1;
            }
        }
        for (int x1=1; x1<x; ++x1) {
            cc += (x-2)*(y-1) + 2 - g[x1][y] - g[x-x1][y];
            cc += 3*(x*y + 2 - x - g[x1][y] - g[x-x1][y]);
        }
        for (int y1=1; y1<y; ++y1) {
            cc += (x-1)*(y-2) + 2 - g[x][y1] - g[x][y-y1];
            cc += 3*(x*y + 2 - y - g[x][y1] - g[x][y-y1]);
        }
        for (int x1=1; x1<x; ++x1) for (int y1=1; y1<y; ++y1) {
            cc += 2*(x*y+x1*y1 + 6 - 2*x - 2*y - g[x1][y] - g[x][y1] - g[x-x1][y-y1]);
            cc += 6*(x*y-x1*y1 + 2 - g[x1][y] - g[x][y1] - g[x-x1][y-y1]);
        }
        c[x][y] = c[y][x] = cc;
    }
}

void solve() {
    long long ans = 0;
    for (int x=1; x<=n; ++x) for (int y=1; y<=n; ++y) ans += (n+1-x)*(n+1-y) * c[x][y];
    cout << n << ' ' << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    init();
    while (cin>>n && n) solve();
    return 0;
}