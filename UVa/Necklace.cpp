/**
 * UVa11255
 * 项链
 */

#include <iostream>
#include <numeric>
using namespace std;

#define N 41
long long c[N][N], s; int a, b, d, n;

void rot(int r) {
    int g = gcd(n, r), l = n/g;
    if (a%l || b%l || d%l) return;
    int x = a/l, y = b/l, z = d/l;
    s += c[x+y+z][x] * c[y+z][y];
}

void flip() {
    int f = (a&1) + (b&1) + (d&1);
    if ((n&1 && f!=1) || (~n&1 && f&1)) return;
    int x = a>>1, y = b>>1, z = d>>1;
    if (f) s += n * c[x+y+z][x] * c[y+z][y];
    else {
        s += n/2 * c[x+y+z][x] * c[y+z][y];
        if (a > 0) s += n/2 * c[x+y+z-1][x-1] * c[y+z][y];
        if (b > 0) s += n/2 * c[x+y+z-1][y-1] * c[z+x][z];
        if (d > 0) s += n/2 * c[x+y+z-1][z-1] * c[y+x][y];
    }
}

void solve() {
    cin >> a >> b >> d;
    n = a + b + d; s = c[n][a] * c[b+d][b];
    for (int i=1; i<n; ++i) rot(i);
    flip();
    cout << s/2/n << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    c[0][0] = 1;
    for (int i=1; i<N; ++i) {
        c[i][0] = 1;
        for (int j=1; j<=i; ++j) c[i][j] = c[i-1][j-1] + c[i-1][j];
    }
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
