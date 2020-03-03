/**
 * UVa103
 * 打结
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 35
#define D 13

bool g[N][N]; int n, d, m[N], a[N], mi, ans;
struct node {
    int a[D];
    bool operator< (const node& rhs) const {
        for (int i=0; i<d; ++i) if (a[i] >= rhs.a[i]) return false;
        return true;
    }
} b[N];

int calc(int i) {
    if (m[i] > 0) return m[i];
    for (int j=1, v; j<=n; ++j) if (g[i][j]) if ((v = calc(j) + 1) > m[i]) {
        m[i] = v; a[i] = j;
    }
    if (m[i] == 0) m[i] = 1, a[i] = 0;
    if (m[i] > ans || (m[i]==ans && i<mi)) ans = m[i], mi = i;
    return m[i];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && cin >> d) {
        memset(g, 0, sizeof(g)); memset(m, 0, sizeof(m)); ans = mi = 1;
        for (int i=1; i<=n; ++i) {
            for (int j=0; j<d; ++j) cin >> b[i].a[j];
            sort(b[i].a, b[i].a+d);
        }
        for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) if (b[i]<b[j]) g[i][j] = true;
        for (int i=1; i<=n; ++i) calc(i);
        cout << ans << endl << mi;
        for (int i = mi; a[i] != 0; i=a[i]) cout << ' ' << a[i];
        cout << endl;
    }
    return 0;
}