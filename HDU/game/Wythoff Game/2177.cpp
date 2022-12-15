/**
 * HDU2177
 * http://acm.hdu.edu.cn/showproblem.php?pid=2177
 * 取石子游戏
 */

#include <iostream>
using namespace std;

#define G 1.61803398874989490253

void solve(int a, int b) {
    int k = a==0 ? 0 : a/G + 1;
    if (a == int(G*k) && b == a+k) {
        cout << 0 << endl;
        return;
    }
    cout << 1 << endl;
    k = G*(b-a);
    if (a >= k) cout << k << ' ' << k+b-a << endl;
    k = b / (G+1) + 1;
    if (b == int((G+1)*k) && a > b-k) cout << b-k << ' ' << b << endl;
    if (a == b) return;
    k = a / (G+1) + 1;
    if (a == int((G+1)*k)) cout << a-k << ' ' << a << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int a, b;
    while (cin>>a>>b && b) solve(a, b);
    return 0;
}