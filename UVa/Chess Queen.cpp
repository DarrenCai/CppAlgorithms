/**
 * UVa11538
 * 象棋中的皇后
 */

#include <iostream>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    long long m, n;
    while (cin>>m>>n && (m || n)) {
        long long x = min(m, n), y = x*(x-1)/2;
        cout << m*n*(n-1) + n*m*(m-1) + 4*(max(m,n)-x+1)*y + 8*y*(x-2)/3 << endl;
    }
    return 0;
}