/**
 * UVa1632
 * 阿里巴巴
 */

#include <iostream>
using namespace std;

#define N 10010
int x[N], d[N], dd[N][N][2], n;

int min(int a, int b) {
    return a < 0 ? b : (b < 0 ? a : (a < b ? a : b));
}

int dp() {
    for (short i=0; i<n; ++i) dd[i][i][0] = dd[i][i][1] = 0;
    for (short l=0; l<n; ++l) for(short i=0, j; (j=i+l) < n; ++i) {
        if (i > 0) {
            int v1 = dd[i][j][0] < 0 ? -1 : dd[i][j][0]-x[i-1]+x[i];
            int v2 = dd[i][j][1] < 0 ? -1 : dd[i][j][1]-x[i-1]+x[j];
            if ((dd[i-1][j][0] = min(v1, v2)) >= d[i-1]) dd[i-1][j][0] = -1;
        }
        if (j+1 < n) {
            int v1 = dd[i][j][0] < 0 ? -1 : dd[i][j][0]-x[i]+x[j+1];
            int v2 = dd[i][j][1] < 0 ? -1 : dd[i][j][1]-x[j]+x[j+1];
            if ((dd[i][j+1][1] = min(v1, v2)) >= d[j+1]) dd[i][j+1][1] = -1;
        }
    }
    return min(dd[0][n-1][0], dd[0][n-1][1]);
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopsen("ou.txt", "w", stdout);
    while (cin >> n) {
        for (short i=0; i<n; ++i) cin >> x[i] >> d[i];
        int ans = dp();
        if (ans >= 0) cout << ans << endl;
        else cout << "No solution" << endl;
    }
    return 0;
}