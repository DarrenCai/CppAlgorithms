/**
 * UVa1073/LA4123
 * 葛伦堡博物馆
 * World Finals >> 2008 - Banff
 */

#include <iostream>
using namespace std;

#define N 505
int n, kase = 0; long long f[N];

long long solve() {
    if (n<4 || n&1) return 0;
    int x = (n+4)>>1;
    return f[x] + f[x-1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    f[3] = 0; f[4] = 1; for (int i=5; i<N; ++i) f[i] = f[i-1]*i/(i-4);
    while (cin>>n && n) cout << "Case " << ++kase << ": " << solve() << endl;
    return 0;
}