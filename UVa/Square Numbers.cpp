/**
 * UVa11461
 * 完全平方数
 */

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int a, b;
    while (cin>>a>>b && a) cout << int(sqrt(b)) - int(sqrt(a-1)) << endl;
    return 0;
}