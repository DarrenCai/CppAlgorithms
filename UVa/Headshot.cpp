/**
 * UVa1636
 * 决斗
 */

#include <iostream>
using namespace std;

#define N 110
char c[N]; short p[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> c) {
        short n = 0, z = 0, s = 0;
        while (c[n]) if (c[n++] == '0') p[z++] = n-1;
        for (short i=0; i<z; ++i) if (c[p[i]==n-1 ? 0 : p[i]+1] == '0') ++s;
        z *= z; s *= n;
        cout << (z>s ? "ROTATE" : (z<s ? "SHOOT" : "EQUAL")) << endl;
    }
    return 0;
}