/**
 * UVa1397/LA3891
 * Tokyo 2007
 */

#include <iostream>
using namespace std;

#define K 33
__int128_t c[K][K]; int a, b, m, n;

void solve() {
    int k = m*n, t = k+1;
    for (int i=0; i<k; ++i) c[i][0] = c[i][1] = c[i][t] = 0;
    c[0][0] = c[1][1] = c[n][1] = c[k][k] = c[k][t] = 1;
    for (int i=2; i<t; ++i) {
        for (int j=0; j<k; ++j) c[j][i] = 0;
        for (int r=0; r<m; ++r) for (int j=0; j<n; ++j) {
            r+1 < m ? c[(r+1)*n + j][i] += c[r*n+j][i-1] : c[j][i] += a*c[r*n+j][i-1];
            j+1<n ? c[r*n + j+1][i] += c[r*n+j][i-1] : c[r*n][i] += b*c[r*n+j][i-1];
        }
    }
    __int128_t x, y;
    for (int i=0; i<k; ++i) for (int j=i; j<k; ++j) if (c[j][i]) {
        if (j > i) for (int z=i; z<t; ++z) y = c[i][z], c[i][z] = c[j][z], c[j][z] = y;
        for (j=i+1; j<k; ++j) while (c[j][i]) {
            x = c[i][i] / c[j][i];
            for (int z=i; z<t; ++z) y = c[j][z], c[j][z] = c[i][z] - x*c[j][z], c[i][z] = y;
        }
        break;
    }
    cout << 1;
    for (int i=k-1; i>=0; --i) {
        for (int j=i+1; j<t; ++j) c[i][t] -= c[i][j]*c[j][t];
        cout << ' ' << int(c[i][t] /= c[i][i]);
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>a>>m>>b>>n && a) solve();
    return 0;
}