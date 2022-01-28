/**
 * UVa1388
 * 墓地雕塑
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int n, m;
    cout << setprecision(8);    // 也可是 cout << fixed << setprecision(4);
    while (cin >> n >> m) {
        int s = 0; m += n;
        for (int i=(n-1)*m; i>0; i-=m) {
            int j = i/n;
            if (j*n < i) s += min(i-j*n, (j+1)*n-i);
        }
        cout << 10000.*s/m/n << endl;
    }
    return 0;
}