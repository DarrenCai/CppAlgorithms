/**
 * HDU1693 Eat the Trees
 * https://vjudge.net/problem/HDU-1693
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 12
long long d[2][1<<N]; int m, n;

long long solve() {
    cin >> n >> m;
    memset(d[0], 0, sizeof(d[0])); d[0][0] = 1;
    for (int i=0, c=1; i<n; ++i) {
        for (int j=0, b; j<m; ++j, c^=1) {
            memset(d[c], 0, sizeof(d[c])); cin >> b;
            for (int k=0, t=1<<m+1; k<t; ++k) if (d[c^1][k]) {
                int l = k & 1<<j, f = k & 2<<j;
                if (b) {
                    if (l ^ f>>1) d[c][k^l^f^1<<j] += d[c^1][k], d[c][k^l^f^2<<j] += d[c^1][k];
                    else d[c][k^3<<j] += d[c^1][k];
                } else if (!l && !f) d[c][k] += d[c^1][k];
            }
        }
        for (int j=(1<<m)-1; j>=0; --j) d[c^1][j<<1] = d[c^1][j], d[c^1][j<<1 | 1] = 0;
    }
    return d[m*n&1][0];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Case " << k << ": There are " << solve() << " ways to eat the trees." << endl;
    return 0;
}