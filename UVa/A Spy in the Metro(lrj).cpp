/**
 * UVa1025
 * 城市里的间谍
 */

#include <iostream>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define T 210
#define N 52

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int k = 0, n;
    while (cin >> n && n) {
        bool l[T][N] = {0}, r[T][N] = {0};
        int t, m, d[N]; cin >> t;
        for (int i=1; i<n; ++i) cin >> d[i];
        cin >> m;
        for (int i=0; i<m; ++i) {
            int v; cin >> v;
            l[v][1] = true;
            for (int i=2; i<n; ++i) l[v += d[i-1]][i] = true;
        }
        cin >> m;
        for (int i=0; i<m; ++i) {
            int v; cin >> v;
            r[v][n] = true;
            for (int i=n-1; i>1; --i) r[v += d[i]][i] = true;
        }
        int f[T][N]; f[t][n] = 0;
        for (int i=1; i<n; ++i) f[t][i] = T;
        for (int i=t-1; i>=0; --i) for (int j=1; j<=n; ++j) {
            f[i][j] = f[i+1][j] + 1;
            if (l[i][j] && (m = i+d[j]) <= t) f[i][j] = min(f[i][j], f[m][j+1]);
            if (r[i][j] && (m = i+d[j-1]) <= t) f[i][j] = min(f[i][j], f[m][j-1]);
        }
        cout << "Case Number " << ++k << ": ";
        if (f[0][1] >= T) {
            cout << "impossible" << endl;
        } else {
            cout << f[0][1] << endl;
        }
    }
    return 0;
}