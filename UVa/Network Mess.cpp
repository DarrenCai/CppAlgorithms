/**
 * UVa1667
 * 乱糟糟的网络
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define M 1050
#define N 60
short a[N][N], d[M][N], c[M], n;

bool check(short i, short j) {
    for (short k=1; k<i; ++k) if (a[i][k]-a[i][k-1] != d[j][k]-d[j][k-1]) return false;
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) {
        for (short i=0; i<n; ++i) for (short j=0; j<n; ++j) cin >> a[i][j];
        short m = n+a[0][1]-1;
        for (short i=n; i<m; ++i) c[i] = 2, d[i][0] = i-n+1, d[i][1] = m-i;
        for (short i=2; i<n; ++i) for (short j=n; j<m; ++j) if (check(i, j)) {
            ++c[j];
            d[j][i] = a[i][0]-d[j][0];
            short mm = m+d[j][i]-1;
            for (short k=n; k<m; ++k) {
                int dd = 0;
                for (short p=0; p<i; ++p) dd = max(dd, abs(d[k][p]-d[j][p]));
                d[k][i] = d[j][i]+dd;
            }
            for (short k=mm-1; k>=m; --k) {
                c[k] = 2; d[k][i] = mm-k;
                for (short p=0; p<i; ++p) d[k][p] = d[j][p]+k-m+1;
            }
            m = mm;
            break;
        }
        sort(c+n, c+m);
        if (m>n) cout << c[n];
        for (short i=n+1; i<m; ++i) cout << ' ' << c[i];
        cout << endl;
    }
    return 0;
}