/**
 * UVa1647
 * 计算机变换
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 1010
unsigned int d[N][35], p = 1000000000; short c[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << setfill('0');
    d[1][0] = 0; c[0] = 1;
    for (short i=2, j, r; i<N; ++i) {
        c[i] = c[i-1];
        for (j=0, r = i&1 ? -1:1; j<c[i]; ++j) {
            d[i][j] = (d[i-1][j]<<1) + r;
            r = d[i][j] / p;
            d[i][j] %= p;
        }
        if (r) d[i][c[i]++] = r;
    }
    short n;
    while (cin >> n) {
        cout << d[n][c[n]-1];
        for (short i=c[n]-2; i>=0; --i) cout << setw(9) << d[n][i];
        cout << endl;
    }
    return 0;
}