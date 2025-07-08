/**
 * HDU1693 Eat the Trees
 * https://vjudge.net/problem/HDU-1693
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 177147
long long d[2][M]; int p[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, M}, m, n;

long long solve() {
    cin >> n >> m;
    memset(d[0], 0, sizeof(d[0])); d[0][0] = 1;
    long long ans = 0;
    for (int i=0, c=1; i<n; ++i) for (int j=0, b; j<m; ++j, c^=1) {
        memset(d[c], 0, sizeof(d[c])); cin >> b;
        for (int k=0; k<p[m]; ++k) if (d[c^1][k]) {
            int x = k / p[m-1];
            if (b) {
                if (x == 2) d[c][k%p[m-1]*3] += d[c^1][k];
                if (x == 1) {
                    if (i+1 < n) d[c][k%p[m-1]*3 + 1] += d[c^1][k];
                    if (j+1 < m) d[c][k%p[m-1]*3 + p[m-1]] += d[c^1][k];
                } else if (!x && j+1<m) d[c][k%p[m-1]*3 + p[m-1] + 1] += d[c^1][k];
            } else if (!x) d[c][3*k] += d[c^1][k];
        }
    }
    return d[m*n&1][0];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int k=1; k<=t; ++k) cout << "Case " << k << ": There are " << solve() << " ways to eat the trees." << endl;
    return 0;
}