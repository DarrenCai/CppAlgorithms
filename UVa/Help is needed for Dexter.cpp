/**
 * UVa11384
 * 正整数序列
 */

#include <iostream>
using namespace std;

int f(int n) {    // 消除递归的写法: int c = 0; while (n) ++c, n>>=1;
    return n==0 ? 0 : 1 + f(n>>1);
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n) cout << f(n) << endl;
    return 0;
}