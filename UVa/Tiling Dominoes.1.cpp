/**
 * UVa11270
 * 铺放骨牌
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 10
long long d[2][1<<N]; int m, n;

long long solve() {
    if (m*n & 1) return 0;
    if (m < n) swap(m, n);
    int t = 1<<n;
    memset(d[0], 0, sizeof(d[0])); d[0][t-1] = 1;
    for (int i=0, c=1; i<m; ++i) for (int j=0; j<n; ++j, c^=1) {
        memset(d[c], 0, sizeof(d[c]));
        for (int k=0; k<t; ++k) if (d[c^1][k]) {
            d[c][k ^ 1<<j] += d[c^1][k];
            if (j && (k & 3<<j-1) == (1<<j)) d[c][k | 1<<j-1] += d[c^1][k];
        }
    }
    return d[m*n & 1][t-1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> m >> n) cout << solve() << endl;
    return 0;
}