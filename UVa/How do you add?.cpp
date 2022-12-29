/**
 * UVa10943
 * 全加和
 */

#include <iostream>
using namespace std;

#define M 1000000
#define N 105
int f[N][N] = {0}, n, k;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=0; i<N; ++i) {
        f[i][1] = 1;
        for (int j=2; j<N; ++j) {
            for (int x=0; x<=i; ++x) f[i][j] += f[i-x][j-1];
            f[i][j] %= M;
        }
    }
    while (cin>>n>>k && n) cout << f[n][k] << endl;
    return 0;
}