/**
 * UVa10870
 * 递推关系
 * 知识点【相伴矩阵/友矩阵】，参见：https://en.wikipedia.org/wiki/Companion_matrix
 */

#include <iostream>
using namespace std;

#define N 16
int a[N][N], b[N][N], c[N][N], f[N], d, n, m;

void matrix_mul(const int (&a)[N][N], const int (&b)[N][N], int (&c)[N][N]) {
    for (int i=0; i<=d; ++i) for (int j=0; j<=d; ++j) {
        int &r = c[i][j] = 0;
        for (int k=0; k<=d; ++k) r = (r + a[i][k]*b[k][j]) % m;
    }
}

void matrix_pow(int (&a)[N][N], int (&c)[N][N], int k) {
    if (k > 1) {
        matrix_pow(a, c, k>>1);
        matrix_mul(c, c, a);
        if (k & 1) return matrix_mul(a, b, c);
    }
    for (int i=0; i<=d; ++i) for (int j=0; j<=d; ++j) c[i][j] = a[i][j];
}

int solve() {
    --n; --d;
    for (int i=0; i<d; ++i) for (int j=0; j<=d; ++j) b[i][j] = a[i][j] = j==i+1;
    for (int i=d; i>=0; --i) cin >> a[d][i], b[d][i] = a[d][i] %= m;
    for (int i=0; i<=d; ++i) cin >> f[i], f[i] %= m;
    if (n <= d) return f[n];
    int r = 0; matrix_pow(a, c, n-d);
    for (int i=0; i<=d; ++i) r = (r + c[d][i]*f[i]) % m;
    return r;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>d>>n>>m && d) cout << solve() << endl;
    return 0;
}