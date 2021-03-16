/**
 * UVa10791
 * 最小公倍数的最小和
 */

#include <iostream>
using namespace std;

unsigned short prim[7000], t=0;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    bool f[65536] = {0};
    for (unsigned short i=2; i<256; ++i) if (!f[i]) for (int j=i*i; j<65535; j+=i) f[j] = true;
    for (unsigned short i=2; i<65535; ++i) if (!f[i]) prim[t++] = i;
    unsigned int n; short k=0;
    while (cin>>n && n) {
        unsigned int sum = 0, v = n, c = 0;
        for (short i=0; v>1 && i<t && (unsigned int)prim[i]*prim[i] <= v; ++i) if (v%prim[i] == 0) {
            unsigned int x = 1;
            while (v%prim[i] == 0) x *= prim[i], v /= prim[i];
            sum += x; ++ c;
        }
        if (v>1 && c>0) sum += v;
        else if (c < 2) sum = n+1;
        cout << "Case " << ++k << ": " << sum << endl;
    }
    return 0;
}