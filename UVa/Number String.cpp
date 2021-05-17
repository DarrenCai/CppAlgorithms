/**
 * UVa1650
 * 数字串
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1010
#define M 1000000007
char s[N]; int d[N][N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    d[0][0] = d[0][2] = 0; d[0][1] = 1;
    while (cin >> s) {
        short n = strlen(s);
        for (short i=1; i<=n; ++i) {
            d[i][0] = d[i][i+2] = 0;
            bool f = i==1 || (s[i-2]=='D');
            if (s[i-1] == '?') {
                int v = f ? d[i-1][1] : d[i-1][i];
                for (short j=1; j<=i+1; ++j) d[i][j] = (d[i][j-1] + v)%M;
            } else if (s[i-1] == 'I') {
                for (short j=1; j<=i+1; ++j)
                    d[i][j] = (M + (d[i][j-1] + (f ? d[i-1][1] - d[i-1][j] : d[i-1][j-1]))%M)%M;
            } else for (short j=i+1; j>0; --j)
                d[i][j] = (M + (d[i][j+1] + (f ? d[i-1][j] : d[i-1][i] - d[i-1][j-1]))%M)%M;
        }
        cout << (s[n-1]=='D' ? d[n][1] : d[n][n+1]) << endl;
    }
    return 0;
}
