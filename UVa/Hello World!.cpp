/**
 * UVa11636
 * 你好　世界！
 */

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short p[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384}, n, kase = 0;
    while (cin>>n && n>=0) cout << "Case " << ++kase << ": " << lower_bound(p, p+15, n) - p << endl;
    return 0;
}