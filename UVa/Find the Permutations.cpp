/**
 * UVa11077
 * 排列统计
 */

#include <iostream>
using namespace std;

#define N 22
unsigned long long d[N][N] = {0}; int n, k;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=1; i<N; ++i) {
        d[i][0] = 1;
        for (int j=1; j<i; ++j) d[i][j] = d[i-1][j] + (i-1)*d[i-1][j-1];
    }
    while (cin>>n>>k && n) cout <<  d[n][k] << endl;
    return 0;
}