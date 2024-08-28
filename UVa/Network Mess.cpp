/**
 * UVa1667/LA3405
 * 乱糟糟的网络
 * Tokyo 2005
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define M 701
#define N 50
int a[N][N], d[M][N], c[M], m, n;

bool check(int i, int j) {
    for (int k=1; k<i; ++k) if (a[i][k]-a[i][k-1] != d[j][k]-d[j][k-1]) return false;
    return true;
}

void solve() {
    for (int i=m=0; i<n; ++i) for (int j=0; j<n; ++j) cin >> a[i][j];
    for (int j=a[0][1]-1; j>0; --j) d[m][0] = m+1, d[m][1] = j, c[m++] = 2;
    for (int i=2; i<n; ++i) for (int j=0; j<m; ++j) if (check(i, j)) {
        ++c[j]; d[j][i] = a[i][0]-d[j][0];
        for (int k=0, dd; k<m; ++k) {
            for (int p=dd=0; p<i; ++p) dd = max(dd, d[k][p]-d[j][p]);
            d[k][i] = d[j][i]+dd;
        }
        for (int k=1; k<d[j][i]; ++k) {
            for (int p=0; p<i; ++p) d[m][p] = d[j][p]+k;
            d[m][i] = d[j][i]-k; c[m++] = 2;
        }
        break;
    }
    sort(c, c+m); cout << c[0];
    for (int i=1; i<m; ++i) cout << ' ' << c[i];
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) solve();
    return 0;
}