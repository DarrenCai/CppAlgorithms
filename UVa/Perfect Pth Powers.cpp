/**
 * UVa10622
 * 完全P次方数
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 46341
#define M 2147483648ll
long long s[32][N], c[32] = {0};

short calc(long long x) {
    long long y = x<0 ? -x : x;
    for (short i=31; i>1; --i) {
        int idx = lower_bound(s[i], s[i]+c[i], y)-s[i];
        if (idx < c[i] && s[i][idx] == y && (x>=0 || i&1)) return i;
    }
    return 1;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (long long i=0, v=i; i<N; ++i, v=i) for (short j=1; j<32 && v<=M; ++j, v*=i) s[j][c[j]++] = v;
    long long n;
    while (cin>>n && n) cout << calc(n) << endl;
    return 0;
}