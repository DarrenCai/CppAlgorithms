/**
 * UVa11040
 * 砌砖
 */

#include <iostream>
using namespace std;

#define N 10
int a[N][N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        for (short i=1; i<N; i+=2) for (short j=1; j<=i; j+=2) cin >> a[i][j];
        for (short i=1; i<N; i+=2) {
            if (i+2 < N) for (short j=1; j<=i; j+=2) a[i+2][j+1] = (a[i][j] - a[i+2][j] - a[i+2][j+2]) >> 1;
            if (i>1) for (short j=2; j<=i; ++j) a[i-1][j-1] = a[i][j-1] + a[i][j];
        }
        for (short i=1; i<N; ++i) {
            cout << a[i][1];
            for (short j=2; j<=i; ++j) cout << ' ' << a[i][j];
            cout << endl;
        }
    }
    return 0;
}