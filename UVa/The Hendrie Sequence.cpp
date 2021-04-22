/**
 * UVa10479
 * Hendrie序列
 */

#include <iostream>
#include <algorithm>
using namespace std;

unsigned long long p[64], q[64][64];

short find(short c, unsigned long long n) {
    if (n == p[max(c-1, 0)]) return c;
    short i = lower_bound(q[c]+1, q[c]+c, n) - q[c], j = c-i-1;
    n -= q[c][i-1];
    short k = max(j-1, 0), l = n/p[k];
    if (n%p[k] == 0) --l;
    return find(j, n - l*p[k]);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    p[0] = 1; for (short i=1; i<64; ++i) p[i] = p[i-1]<<1;
    for (short i=2; i<64; ++i) {
        q[i][i-1] = p[i-1]-1; q[i][0] = 0;
        for (short j=i-2; j>0; --j) q[i][j] = q[i][j+1] - (j+1)*p[max(i-3-j,0)];
    }
    unsigned long long n;
    while (cin>>n && n) {
        short c = lower_bound(p, p+64, n) - p;
        cout << find(c, n-(c==0 ? 0 : p[c-1])) << endl;
    }
    return 0;
}