/**
 * UVa1645
 * 统计有根树
 */

#include <iostream>
using namespace std;

#define N 1010
#define M 1000000007
int d[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    d[1] = 1;
    for (short i=2, v; i<N; ++i) {
        d[i] = d[v=i-1];
        for (short j=v>>1; j>1; --j) if (v%j==0) d[i] = (d[i] + d[v/j]) % M;
        if (v > 1) d[i] = (d[i] + d[1]) % M;
    }
    short kase = 0, n;
    while (cin>>n) cout << "Case " << ++kase << ": " << d[n] << endl;
    return 0;
}