/**
 * HDU1847
 * http://acm.hdu.edu.cn/showproblem.php?pid=1847
 */

#include <iostream>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int n;
    while (cin >> n) cout << (n%3 ? "Kiki" : "Cici") << endl;
    return 0;
}