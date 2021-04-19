/**
 * UVa1644
 * 素数间隔
 */

#include <iostream>
#include <algorithm>
using namespace std;

bool flag[1299710] = {false}; int prim[100000];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<1141; ++i) if (!flag[i]) for (int j=i*i; j<1299710; j+=i) flag[j] = true;
    for (int i=2, t=0; i<1299710; ++i) if (!flag[i]) prim[t++] = i;
    int n;
    while (cin>>n && n) {
        if (flag[n]) {
            int i = upper_bound(prim, prim+100000, n) - prim;
            cout << prim[i] - prim[i-1] << endl;
        } else cout << 0 << endl;
    }
    return 0;
}