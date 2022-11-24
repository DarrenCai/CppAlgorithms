/**
 * UVa10253
 * 串并联网络
 */

#include <iostream>
using namespace std;

#define N 32
int n; long long g[N][N] = {0};

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    g[1][1] = 1;
    for (int i=2; i<N; ++i) {
        g[0][i] = 1;
        for (int j=1; j<i; ++j) {
            long long x0 = g[j][j], x = x0, y = i/j;
            g[i][i] += x * g[i-j][j+1];
            for (int k=1; k<y; ++k) {
                x = x*(x0+k)/(k+1);
                g[i][i] += x * g[i - (k+1)*j][j+1];
            }
        }
        for (int j=i-1; j>0; --j) {
            g[i][j] = g[i][j+1];
            long long x0 = g[j][j], x = x0, y = i/j;
            g[i][j] += x * g[i-j][j+1];
            for (int k=1; k<y; ++k) {
                x = x*(x0+k)/(k+1);
                g[i][j] += x * g[i - (k+1)*j][j+1];
            }
        }
    }
    while (cin>>n && n) cout << g[n][1] << endl;
    return 0;
}