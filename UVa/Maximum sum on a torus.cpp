/**
 * UVa10827
 * 环面上的最大和
 */

#include <iostream>
using namespace std;

#define N 160
int a[N][N], s[N], t[N]={0}, q[N], n;

int solve() {
    cin >> n;
    for (int i=1; i<=n; ++i) {
        for (int j=0; j<n; ++j) cin >> a[i][j];
        for (int j=1; j<n; ++j) a[i][n+j-1] = a[i][j-1]; 
    }
    int m = 2*n, ans = a[1][0];
    for (int i=1; i<n; ++i) for (int j=m-2; j>=0; --j) a[n+i][j] = a[i][j];
    for (int y=0; y<n; ++y) {
        for (int i=0; i<m; ++i) s[i] = 0;
        for (int l=0; l<n; ++l) {
            int head = 0, tail = 0; q[0] = 0;
            for (int x=1; x<m; ++x) {
                s[x] += a[x][y+l]; t[x] = t[x-1] + s[x];
                while (x-q[head]>n) ++head;
                ans = max(ans, t[x] - t[q[head]]);
                while (head<=tail && t[x] <= t[q[tail]]) --tail;
                q[++tail] = x;
            }
        }
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}