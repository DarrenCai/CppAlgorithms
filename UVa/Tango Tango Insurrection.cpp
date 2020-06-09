/**
 * UVa10618
 * 跳舞机
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 75
char s[N], a[]="LURD";
short fs[] = {1, 2, 3, 4, 6, 7, 9, 11, 12, 13, 14}, d[N][11][3], ans[N][11][3],
    sf[] = {0, 0, 1, 2, 3, 0, 4, 5, 0, 6, 0, 7, 8, 9, 10};

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou1.txt", "w", stdout);
    while (cin >> s) {
        if (s[0] == '#') return 0;
        short n = strlen(s);
        memset(d[n], 0, sizeof(d[n]));
        for (short p=n-1; p>=0; --p) for (short i=0; i<11; ++i)
            if (s[p] == '.') {
                for (short j=0; j<3; ++j) d[p][i][j] = d[p+1][i][2], ans[p][i][j] = i;
                if (fs[i] != 4 && fs[i] != 12) {
                    for (short k=0; k<4; ++k) if (k != (fs[i]&3) && k != fs[i]>>2) {
                        short r = d[p+1][sf[k<<2 | fs[i]&3]][0];
                        for (short j=0; j<3; ++j) {
                            short cost = j==0 ? ((k&1) != (fs[i]>>2&1) ? 5 : 7) : 1;
                            if (r+cost < d[p][i][j]) d[p][i][j] = r+cost, ans[p][i][j] = sf[k<<2 | fs[i]&3];
                        }
                    }
                }
                if (fs[i] != 9 && fs[i] != 11) {
                    for (short k=0; k<4; ++k) if (k != (fs[i]&3) && k != fs[i]>>2) {
                        short r = d[p+1][sf[fs[i]&12 | k]][1];
                        for (short j=0; j<3; ++j) {
                            short cost = j==1 ? ((k&1) != (fs[i]&1) ? 5 : 7) : 1;
                            if (r+cost < d[p][i][j]) d[p][i][j] = r+cost, ans[p][i][j] = sf[fs[i]&12 | k];
                        }
                    }
                }
            } else if (a[fs[i]>>2] == s[p]) for (short j=0; j<3; ++j) {
                d[p][i][j] = d[p+1][i][0] + (j==0 ? 3 : 1), ans[p][i][j] = i;
            } else if (a[fs[i]&3] == s[p]) for (short j=0; j<3; ++j) {
                d[p][i][j] = d[p+1][i][1] + (j==1 ? 3 : 1), ans[p][i][j] = i;
            } else if (fs[i] == 9 || fs[i] == 11) for (short j=0; j<3; ++j) {
                ans[p][i][j] = sf[(s[p]=='L' ? 0 : (s[p]=='U' ? 1 : 3))<<2 | fs[i]&3];
                d[p][i][j] = d[p+1][ans[p][i][j]][0] + (j==0 ? (s[p]=='L' ? 7 : 5) : 1);
            } else if (fs[i] == 4 || fs[i] == 12) for (short j=0; j<3; ++j) {
                ans[p][i][j] = sf[fs[i]&12 | (s[p]=='R' ? 2 : (s[p]=='U' ? 1 : 3))];
                d[p][i][j] = d[p+1][ans[p][i][j]][1] + (j==1 ? (s[p]=='R' ? 7 : 5) : 1);
            } else {
                short k = s[p]=='L' ? 0 : (s[p]=='U' ? 1 : (s[p]=='R' ? 2 : 3));
                for (short j=0; j<3; ++j) {
                    d[p][i][j] = d[p+1][sf[k<<2 | fs[i]&3]][0] + (j==0 ? ((k&1) != (fs[i]>>2&1) ? 5 : 7) : 1);
                    ans[p][i][j] = sf[k<<2 | fs[i]&3];
                    short r = d[p+1][sf[fs[i]&12 | k]][1] + (j==1 ? ((k&1) != (fs[i]&1) ? 5 : 7) : 1);
                    if (r < d[p][i][j]) d[p][i][j] = r, ans[p][i][j] = sf[fs[i]&12 | k];
                }
            }
        for (short p=0, i=1, j=2, ii, k; p<n; ++p, i=ii) {
            ii = ans[p][i][j], k = s[p]=='L' ? 0 : (s[p]=='U' ? 1 : (s[p]=='R' ? 2 : 3));
            j = (i==ii ? (s[p]=='.' ? 2 : (fs[i]>>2 == k ? 0 : 1)) : (fs[i]>>2 != fs[ii]>>2 ? 0 : 1));
            cout << (j==2 ? '.' : (j==0 ? 'L' : 'R'));
        }
        cout << endl;
    }
    return 0;
}