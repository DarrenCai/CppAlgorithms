/**
 * HDU2147
 * http://acm.hdu.edu.cn/showproblem.php?pid=2147
 */

#include <iostream>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int m, n;
    while (cin>>m>>n && m) cout << (m&1 && n&1 ? "What a pity!" : "Wonderful!") << endl;
    return 0;
}