/**
 * UVa1637
 * 纸牌游戏
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

char s[9][5][3]={0}, buf[9]; double d[1953125];
const int pow[] = {1, 5, 25, 125, 625, 3125, 15625, 78125, 390625};

double dp(int c) {
    double& ref = d[c];
    if (ref >= .0) return ref;
    for (int i=0, j=c; i<9; ++i, j/=5) buf[i] = s[i][j%5][0];
    bool visit[9] = {false}; short p[4][4], cnt[4], n = 0;
    for (short i=0; i<9; ++i) if (buf[i] && !visit[i]) {
        visit[i] = true; short cc = 1; p[n][0] = i;
        for (short j=i+1; j<9; ++j) if (buf[j] == buf[i]) visit[p[n][cc++] = j] = true;
        if (cc > 1) cnt[n++] = cc;
    }
    if (n == 0) return ref = .0;
    short s = 0; for (short i=0; i<n; ++i) s += cnt[i]*(cnt[i]-1)>>1;
    ref = .0;
    for (short i=0; i<n; ++i) for (short j=0; j<cnt[i]; ++j) for (short k=j+1; k<cnt[i]; ++k)
        ref += dp(c-pow[p[i][j]]-pow[p[i][k]]);
    return ref /= s;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(6);
    while (!cin.eof()) {
        for (short i=0; i<9; ++i) for (short j=1; j<5; ++j) cin >> s[i][j];
        fill_n(d, 1953125, -1.); d[0] = 1.;
        cout << dp(1953124) << endl;
    }
    return 0;
}