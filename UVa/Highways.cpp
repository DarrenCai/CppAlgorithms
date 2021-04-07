/**
 * UVa1393
 * 高速公路
 */

#include <iostream>
using namespace std;

#define N 310
int d[N][N] = {0};

int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else {
        if (b & 1) return gcd(a >> 1, b);
        return gcd(a >> 1, b >> 1) << 1;
    }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    d[1][1] = 1;
    for (short i=2; i<N; ++i) {
        short t = 0;
        for (short j=1; j<i; ++j) {
            if (gcd(j, i) == 1) ++t;
            d[i][j] = d[j][i] = d[j][i-1] + t;
        }
        d[i][i] = d[i-1][i] + t;
    }
    short m, n;
    while (cin>>m>>n && m && n) {
        int s = 0;
        for (short i=0; i<m; ++i) for (short j=0; j<n; ++j) {
            short b = n-1-j;
            s += d[i][b] - d[i>>1][b>>1];
        }
        cout << (s<<1) << endl;
    }
    return 0;
}