/**
 * UVa1631
 * 密码锁
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 1010
#define INF 5050
#define rev(d) ((d)==0 ? 0 : 10-(d))
char s1[N], s2[N]; short n, up[N], d[10][10][N];

short dp(short up1=0, short up2=0, short i=0) {
    short &ref = d[up1][up2][i], down1 = rev(up1), down2 = rev(up2);
    if (ref < INF) return ref;
    if (i==n) {
        ref = min(max(up1, up2), max(down1, down2));
        return ref = min(int(ref), min(up1+down2, down1+up2));
    }
    short up3 = up[i], down3 = rev(up3);
    ref = min(up1, down1) + dp(up2, up3, i+1);
    for (short j=up1; j>=0; --j)
        ref = min(int(ref), up1 + dp(up2>=j ? up2-j : 10+up2-j, up3, i+1));
    for (short j=down1; j>=0; --j)
        ref = min(int(ref), down1 + dp(down2>=j ? rev(down2-j) : j-down2, up3, i+1));
    for (short j=up1; j>=0; --j) for (short jj=j; jj>=0; --jj)
        ref = min(int(ref), up1 + dp(up2>=j ? up2-j : 10+up2-j, up3>=jj ? up3-jj : 10+up3-jj, i+1));
    for (short j=down1; j>=0; --j) for (short jj=j; jj>=0; --jj)
        ref = min(int(ref), down1 + dp(down2>=j ? rev(down2-j) : j-down2, down3>=jj ? rev(down3-jj) : jj-down3, i+1));
    return ref;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> s1 && cin >> s2) {
        n = strlen(s1); memset(d, 20, sizeof(d));
        for (short i=0; i<n; ++i) {
            up[i] = s2[i] - s1[i]; if (up[i] < 0) up[i] += 10;
        }
        cout << dp() << endl;
    }
    return 0;
}