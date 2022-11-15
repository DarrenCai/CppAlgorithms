/**
 * UVa1632
 * 阿里巴巴
 */

#include <iostream>
using namespace std;

#define N 10010
int x[N], d[N], dd[2][N][2], n;

int min(int a, int b) {
    return a < 0 ? b : (b < 0 ? a : (a < b ? a : b));
}

int dp() {
    int cur = 0, nex = 1;
    for (short i=0; i<n; ++i) dd[0][i][0] = dd[0][i][1] = 0;
    for (short l=0; l<n; ++l) {
        for(short i=0, j; (j=i+l) < n; ++i) {
            int t = min(dd[cur][i][0], dd[cur][i][1]);
            if (t < 0 || (t >= d[i] && t >= d[j])) return -1;
            if (i > 0) {
                int v1 = dd[cur][i][0] < 0 ? -1 : dd[cur][i][0]-x[i-1]+x[i];
                int v2 = dd[cur][i][1] < 0 ? -1 : dd[cur][i][1]-x[i-1]+x[j];
                if ((dd[nex][i-1][0] = min(v1, v2)) >= d[i-1]) dd[nex][i-1][0] = -1;
            }
            if (j+1 < n) {
                int v1 = dd[cur][i][0] < 0 ? -1 : dd[cur][i][0]-x[i]+x[j+1];
                int v2 = dd[cur][i][1] < 0 ? -1 : dd[cur][i][1]-x[j]+x[j+1];
                if ((dd[nex][i][1] = min(v1, v2)) >= d[j+1]) dd[nex][i][1] = -1;
            }
        }
        cur ^= 1; nex ^= 1;
    }
    return min(dd[nex][0][0], dd[nex][0][1]);
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        for (short i=0; i<n; ++i) cin >> x[i] >> d[i];
        int ans = dp();
        if (ans >= 0) cout << ans << endl;
        else cout << "No solution" << endl;
    }
    return 0;
}