/**
 * UVa1423
 * Guess
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 12
short a[N], b[N], m[N][N];

bool cmp(short x, short y) {
    return y>x ? m[x+1][y]>0 : m[y+1][x]<0;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        short n, k; char c; cin >> n; ++n; a[0] = b[0] = 0;
        for (short i=1; i<n; ++i) {
            a[i] = i;
            for (short j=i; j<n; ++j) cin >> c, (m[i][j] = c=='0' ? 0 : (c=='-' ? -1 : 1));
        }
        for (short i=1; i<n; ++i) m[0][i] = m[1][i];
        sort(a, a+n, cmp);
        for (short i=0; i<n; ++i) if (a[i] == 0) k = i;
        for (short i=k+1; i<n; ++i) b[a[i]] = b[a[i-1]] + (cmp(a[i-1], a[i]) ? 1 : (cmp(a[i], a[i-1]) ? -1 : 0));
        for (short i=k; i>0; --i) b[a[i-1]] = b[a[i]] + (cmp(a[i-1], a[i]) ? -1 : (cmp(a[i], a[i-1]) ? +1 : 0));
        --n;
        for (short i=1; i<=n; ++i) {
            cout << b[i]-b[i-1];
            i<n ? cout << ' ' : cout << endl;
        }
    }
    return 0;
}