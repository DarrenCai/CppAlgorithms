/**
 * UVa10271
 * 佳佳的筷子
 */

#include <iostream>
using namespace std;

#define N 5020
#define K 1020
int d[N][K]={0}, c[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        short k, n; cin >> k >> n; k += 8;
        for (short i=0; i<n; ++i) cin >> c[i];
        for (short i=2; i<=n; ++i) for (short j=0; 3*j<=i && j<=k; ++j) {
            int &ref = d[i][j];
            if (i == 3*j) ref = d[i-2][j-1] + (c[n-i+1]-c[n-i])*(c[n-i+1]-c[n-i]);
            else {
                ref = d[i-1][j];
                if (j > 0) ref = min(ref, d[i-2][j-1] + (c[n-i+1]-c[n-i])*(c[n-i+1]-c[n-i]));
            }
        }
        cout << d[n][k] << endl;
    }
    return 0;
}