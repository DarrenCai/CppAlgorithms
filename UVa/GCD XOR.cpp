/**
 * UVa12716
 * GCD等于XOR
 */

#include <iostream>
using namespace std;

#define M 30000100
int cnt[M] = {0}, d[M];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int g=1, m=M/3; g<=m; ++g) for (int gg=g<<1, a=g+gg; a <= M; a+=gg) if ((a&g) == g) ++cnt[a];
    d[0] = 0; for (int a=1; a<=M; ++a) d[a] = d[a-1] + cnt[a];
    short t; cin >> t;
    for (short kase=1; kase <= t; ++kase) {
        int n; cin >> n;
        cout << "Case " << kase << ": " << d[n] << endl;
    }
    return 0;
}