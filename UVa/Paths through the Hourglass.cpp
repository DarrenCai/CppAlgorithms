/**
 * UVa10564
 * 沙漏里的路径
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 42
#define S 510
long long d[N][N][S]; char p[N][N][S]; int x[N][N>>1], n, s;

void solve() {
    int m = (n-1)<<1, t = 9*(m+1), f; long long c = 0;
    for (int i=0; i<n; ++i) for (int j=0, k=n-i; j<k; ++j) cin >> x[i][j];
    for (int i=n; i<=m; ++i) for (int j=0, k=i-n+2; j<k; ++j) cin >> x[i][j];
    memset(d, 0, sizeof(d)); memset(p, 0, sizeof(p));
    for (int i=0; i<n; ++i) d[m][i][x[m][i]] = 1;
    for (int i=m; i>=n; --i) for (int v=0; v<=t; ++v) {
        for (int j=0, k=i-n+1; j<k; ++j) {
            int s = v + x[i-1][j];
            if (d[i-1][j][s] = d[i][j][v]) p[i-1][j][s] = 'L';
        }
        for (int j=1, k=i-n+2; j<k; ++j) {
            int s = v + x[i-1][j-1];
            if ((d[i-1][j-1][s] += d[i][j][v]) && !p[i-1][j-1][s]) p[i-1][j-1][s] = 'R';
        }
    }
    for (int i=n-1; i>0; --i) for (int v=0; v<=t; ++v) for (int j=0, k=n-i; j<k; ++j) {
        int s = v + x[i-1][j+1];
        if (d[i-1][j+1][s] = d[i][j][v]) p[i-1][j+1][s] = 'L';
        s = v + x[i-1][j];
        if ((d[i-1][j][s] += d[i][j][v]) && !p[i-1][j][s]) p[i-1][j][s] = 'R';
    }
    for (int i=0; i<n; ++i) if (d[0][i][s]) {
        if (!c) f = i;
        c += d[0][i][s];
    }
    cout << c << endl;
    if (c) {
        cout << f << ' ';
        for (int i=0, j=n-1; i<j; ++i) {
            cout << p[i][f][s];
            int s1 = s - x[i][f];
            f = p[i][f][s]=='L' ? f-1 : f;
            s = s1;
        }
        for (int i=n-1; i<m; ++i) {
            cout << p[i][f][s];
            int s1 = s - x[i][f];
            f = p[i][f][s]=='L' ? f : f+1;
            s = s1;
        }
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n>>s && n) solve();
    return 0;
}