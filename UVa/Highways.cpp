/**
 * UVa1393/LA3720
 * 高速公路
 * CERC 2006
 */

#include <iostream>
using namespace std;

#define N 305
int f[N+1][N+1] = {0}, c[N+1][N+1] = {0};

bool coprime(int a, int b) {
    if (a > b) return coprime(b, a);
    if (a == 0) return b==1;
    if (a & 1) {
        if (b & 1) return coprime(a, (b-a)>>1);
        return coprime(a, b>>1);
    } else if (b & 1) return coprime(a>>1, b);
    return false;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=1; i<N; ++i) for (int j=1; j<N; ++j) c[i][j] = 2*coprime(i, j) + c[i][j-1];
    for (int i=1; i<N; ++i) for (int j=1; j<N; ++j)
        f[i+1][j+1] = 2*f[i][j+1] - f[i-1][j+1] + c[i][j] - (i&1 ? 0 : c[i/2][j/2]);
    for (int i=2; i<=N; ++i) for (int j=2; j<=N; ++j) f[i][j] += f[i][j-1];
    int m, n;
    while (cin>>n>>m && n) cout << f[m][n] << endl;
    return 0;
}