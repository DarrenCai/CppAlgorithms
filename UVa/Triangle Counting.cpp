/**
 * UVa11401
 * 数三角形
 */

#include <iostream>
using namespace std;

#define N 1000010
long long f[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    long long n; f[3] = 0;
    for (n=4; n<N; ++n) {
        long long c = (n-2)>>1;
        f[n] = f[n-1] + c*(n-2-c);
    }
    while (cin>>n && n>2) cout << f[n] << endl;
    return 0;
}