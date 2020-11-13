/**
 * UVa10285
 * 最长的滑雪路径
 */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define N 110
short h[N][N], d[N][N], r, c, n, ans;
struct Node {
    short r, c;
    bool operator< (const Node& rhs) const {
        return h[r][c] < h[rhs.r][rhs.c];
    }
} nodes[N*N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    string s; short t; cin >> t;
    while (t--) {
        cin >> s >> r >> c; n = 0; ans = 1;
        for (short i=0; i<r; ++i) for (short j=0; j<c; ++j) cin >> h[i][j], d[i][j] = 1, nodes[n].r=i, nodes[n++].c=j;
        sort(nodes, nodes+n);
        for (short ii=0; ii<n; ++ii) {
            short i = nodes[ii].r, j = nodes[ii].c;
            if (i>0 && h[i-1][j] > h[i][j] && d[i][j] >= d[i-1][j]) ans = max(ans, d[i-1][j] = d[i][j] + 1);
            if (i+1<r && h[i+1][j] > h[i][j] && d[i][j] >= d[i+1][j]) ans = max(ans, d[i+1][j] = d[i][j] + 1);
            if (j>0 && h[i][j-1] > h[i][j] && d[i][j] >= d[i][j-1]) ans = max(ans, d[i][j-1] = d[i][j] + 1);
            if (j+1<c && h[i][j+1] > h[i][j] && d[i][j] >= d[i][j+1]) ans = max(ans, d[i][j+1] = d[i][j] + 1);
        }
        cout << s << ": " << ans << endl;
    }
    return 0;
}