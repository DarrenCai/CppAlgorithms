/**
 * UVa11925
 * 生成排列
 */

#include <iostream>
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n, a[300], q[300];
    while (cin >> n && n) {
        for (short i=0; i<n; ++i) cin >> a[i], q[i] = i+1;
        for (short i=n-1; i>=0; --i)
            for (short j=1; j<n; ++j) if (q[j] == a[i]) {
                for (short k=0; k<j; ++k) cout << '2';
                for (short k=j+1; k<n; ++k) cout << "12";
                while (j--) q[j+1] = q[j]; q[0] = a[i];
                break;
            }
        cout << endl;
    }
    return 0;
}