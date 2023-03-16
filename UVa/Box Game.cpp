/**
 * UVa12293
 * 盒子游戏
 */

#include <iostream>
using namespace std;

int n;
bool solve() {
    ++n;
    return (n&(-n)) != n;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) cout << (solve() ? "Alice" : "Bob") << endl;
    return 0;
}