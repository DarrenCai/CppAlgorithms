/**
 * UVa11728
 * 已知因子之和
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1005
int f[N], s, kase = 0;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    memset(f, -1, sizeof(f));
    for (int i=1; i<N; ++i) {
        s = 0;
        for (int j=1; j*j <= i; ++j) if (i%j ==0) {
            s += j;
            int k = i/j;
            if (k <= j) break;
            s += k;
        }
        if (s < N) f[s] = i;
    }
    while (cin>>s && s) cout << "Case " << ++kase << ": " << f[s] << endl;
    return 0;
}