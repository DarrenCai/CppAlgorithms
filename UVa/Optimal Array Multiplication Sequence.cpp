/**
 * UVa348
 * 最优矩阵链乘
 */

#include <iostream>
using namespace std;

#define N 15
int d[N][N] = {0}, f[N][N], p[N], n, k=0;

void print(int i, int j) {
    if (i == j) {
        cout << 'A' << i;
    } else {
        cout << '(';
        print(i, f[i][j]);
        cout << " x ";
        print(f[i][j]+1, j);
        cout << ')';
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) {
        for (int i=1; i<=n; ++i) cin >> p[i] >> p[i+1];
        for (int l=1; l<n; ++l) for (int i=1; i+l<=n; ++i) {
            d[i][i+l] = d[i][i] + p[i] * p[i+1] * p[i+l+1] + d[i+1][i+l]; f[i][i+l] = i;
            for (int l1=1; l1<l; ++l1) {
                int v = d[i][i+l1] + p[i] * p[i+l1+1] * p[i+l+1] + d[i+l1+1][i+l];
                if (v < d[i][i+l]) d[i][i+l] = v, f[i][i+l] = i+l1;
            }
        }
        cout << "Case " << ++k << ": ";
        print(1, n);
        cout << endl;
    }
    return 0;
}