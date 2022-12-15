/**
 * HDU2897
 * http://acm.hdu.edu.cn/showproblem.php?pid=2897
 * 邂逅明下
 */

#include <iostream>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int n, p, q;
    while (cin >> n >> p >> q) {
        int r = n % (p+q);
        cout << (r>0 && r<=p ? "LOST" : "WIN") << endl;
    }
    return 0;
}