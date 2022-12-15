/**
 * HDU1527
 * http://acm.hdu.edu.cn/showproblem.php?pid=1527
 * 取石子游戏
 */

#include <iostream>
using namespace std;

#define G 1.61803398874989490253

int solve(int a, int b) {
    int k = a==0 ? 0 : a/G + 1;
    return a == int(G*k) && b == a+k ? 0 : 1;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int a, b;
    while (cin >> a >> b) cout << solve(min(a, b), max(a, b)) << endl;
    return 0;
}