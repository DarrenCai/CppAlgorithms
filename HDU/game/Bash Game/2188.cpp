/**
 * HDU2188
 * http://acm.hdu.edu.cn/showproblem.php?pid=2188
 * 悼念512汶川大地震遇难同胞——选拔志愿者
 */

#include <iostream>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int m, n, t; cin >> t;
    while (t--) {
        cin >> n >> m;
        cout << (n%(m+1) ? "Grass" : "Rabbit") << endl;
    }
    return 0;
}