/**
 * UVa1386/LA3704
 * 细胞自动机
 * NEERC 2006
 */

#include <iostream>
using namespace std;

#define N 502
int a[N], b[N], c[N], f[N], n, m, d, k;

void matrix_mul(const int (&a)[N], const int (&b)[N], int (&c)[N]) {
    for (int i=0; i<n; ++i) {
        c[i] = 0;
        for (int j=0; j<n; ++j) c[i] = (c[i] + a[j] * (long long)b[i<j ? n+i-j : i-j]) % m;
    }
}

void matrix_pow(int (&a)[N], int (&c)[N], int k) {
    if (k > 1) {
        matrix_pow(a, c, k>>1);
        matrix_mul(c, c, a);
        if (k & 1) return matrix_mul(a, b, c);
    }
    for (int i=0; i<n; ++i) c[i] = a[i];
}

void solve() {
    for (int i=0; i<n; ++i) cin >> f[i], a[i] = b[i] = i<=d || i>=n-d;
    matrix_pow(a, c, k);
    for (int i=0, r; i<n; ++i) {
        for (int j=r=0; j<n; ++j) r = (r + c[j] * (long long)f[i+j<n ? i+j : i+j-n]) % m;
        if (i) cout << ' ';
        cout << r;
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin >> n >> m >> d >> k) solve();
    return 0;
}