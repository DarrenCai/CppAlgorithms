/**
 * UVa1418
 * 梦之队
 */

#include <iostream>
using namespace std;

short solve(short n) {
    short ans = 1, m = (n-1)<<1, c = n-3;
    if (c >= 0) {
        if (m-2 > 3+c) return n;
        if (m-1 > 3+c) return c+1;
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n;
    while (cin>>n && n) cout << solve(n) << endl;
    return 0;
}
