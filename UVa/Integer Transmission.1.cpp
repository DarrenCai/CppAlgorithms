/**
 * UVa1228/LA4031
 * 整数传输
 * Beijing 2007
 */

#include <iostream>
using namespace std;

#define ULL unsigned long long
#define N 65
int a[N] = {0}, b[N] = {0}, n, d, kase = 0; ULL f[N][N], k;

void solve() {
    int x = 0, y = 0;
    for (ULL i=0, v=k; i<n; ++i, v>>=1) v&1 ? a[++x] = i : b[++y] = i;
    f[x][y] = 1;
    for (int i=y; i>0; --i) f[x][i-1] = b[i]+d >= a[x];
    for (int i=x-1; i>=0; --i) {
        f[i][y] = a[i+1]+d >= b[y];
        for (int j=y; j>0; --j)
            f[i][j-1] = b[j]+d >= a[i] && a[i+1]+d >= b[j-1] ? f[i+1][j-1] + f[i][j] : 0;
    }
    ULL g = 0, h = 0;
    for (int i=1, j=0, k=0; i<=n; ++i) {
        i-j > x || (j<y && b[j+1]+d < a[i-j]) ? ++j : g += 1ull<<(i-1);
        i-k > x || (k<y && a[i-k]+d >= b[k+1]) ? ++k : h += 1ull<<(i-1);
    }
    cout << "Case " << ++kase << ": " << f[0][0] << ' ' << g << ' ' << h << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n>>d>>k && n) solve();
    return 0;
}