/**
 * UVa437
 * 巴比伦塔
 */

#include <iostream>
#include <cstring>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define max(a, b) (a>b ? a:b)
const int N = 95;

struct item {
    int l, w, h;
    item(){}
    item(int a, int b, int h):l(min(a,b)), w(max(a,b)), h(h) {}
    bool operator< (const item& rhs) const {
        return l < rhs.l && w < rhs.w;
    }
} a[N];

bool g[N][N]; int f[N], n, ans;

int calc(int i) {
    if (f[i] > 0) return f[i];
    f[i] = a[i].h;
    for (int j=0; j<n; ++j) if (g[i][j]) f[i] = max(f[i], calc(j) + a[i].h);
    ans = max(ans, f[i]);
    return f[i];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int k = 0;
    while (cin >> n && n) {
        for (int i=0; i<n; ++i) {
            int x, y, z, p=3*i;
            cin >> x >> y >> z;
            a[p] = item(x, y, z); a[p+1] = item(x, z, y); a[p+2] = item(y, z, x);
        }
        n *= 3;
        for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) g[j][i] = a[i] < a[j];
        memset(f, 0, sizeof(f)); ans = 0;
        for (int i=0; i<n; ++i) calc(i);
        cout << "Case " << ++k << ": maximum height = " << ans << endl;
    }
    return 0;
}