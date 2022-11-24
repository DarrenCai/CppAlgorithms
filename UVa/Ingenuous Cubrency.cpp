/**
 * UVa11137
 * 立方数之和
 */

#include <iostream>
using namespace std;

#define N 10010
#define M 22
long long e[N][M], d[N]; int f[N], n;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    d[0] = 0;
    for (int i=1; i<N; ++i) {
        d[i] = e[i][1] = f[i] = 1;
        for (int j=2; j<M; ++j) {
            int k = i - j*j*j;
            if (k < 0) break;
            f[i] = j;
            d[i] = e[i][j] = e[i][j-1] + (k>0 ? e[k][min(f[k], j)] : 1);
        }
    }
    while (cin >> n) cout << d[n] << endl;
    return 0;
}