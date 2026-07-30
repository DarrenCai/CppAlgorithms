/**
 * UVa1305/LA2522
 * Beijing 2002
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define C 101
double a[C][C], b[C][C], t[C][C]; int c, n, m;

void mul(double (&a)[C][C], const double (&b)[C][C]) {
    for (int i=0; i<c; ++i) for (int j=0; j<c; ++j) {
        t[i][j] = 0.;
        for (int k=0; k<c; ++k) t[i][j] += a[i][k]*b[k][j];
    }
    for (int i=0; i<c; ++i) for (int j=0; j<c; ++j) a[i][j] = t[i][j];
}

void pow(int x) {
    while (x) {
        if (x & 1) mul(b, a);
        mul(a, a); x >>= 1;
    }
}

double solve() {
    cin >> n >> m;
    if (m > c || (m^n)&1) return 0.;
    for (int i=0; i<=c; ++i) {
        if (i<c) a[i+1][i] = (i+1.)/c;
        if (i) a[i-1][i] = (c-i+1.)/c;
        for (int j=0; j<=c; ++j) if (abs(i-j) != 1) a[j][i] = 0.;
    }
    for (int i=0; i<=c; ++i) for (int j=0; j<=c; ++j) {
        b[i][j] = 0.;
        for (int k=0; k<=c; ++k) b[i][j] += a[i][k]*a[k][j];
    }
    for (int i=n&1; i<=c; i+=2) for (int j=n&1; j<=c; j+=2) a[i>>1][j>>1] = b[i][j];
    c = n&1 ? c+1 >> 1 : (c>>1) + 1;
    for (int i=0; i<c; ++i) for (int j=0; j<c; ++j) b[i][j] = i==j ? 1. : 0.;
    pow(n >> 1);
    return b[0][m>>1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    while (cin >> c && c) cout << solve() << endl;
    return 0;
}
