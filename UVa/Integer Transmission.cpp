/**
 * UVa1228
 * 整数传输
 */

#include <iostream>
using namespace std;

#define N 64
#define max(a, b) (a>b ? a:b)
#define min(a, b) (a<b ? a:b)
#define ULL unsigned long long
ULL dp[N+1][N+1]; short a0[N], a1[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n, d, kase=0; ULL k;
    while (cin >> n >> d >> k && n) {
        short t0=0, t1=0; ULL k1 = k;
        for (short i=n-1; i>=0; --i, k>>=1) k&1 ? a1[t1++]=i : a0[t0++]=i;
        if (t0==0 || t1==0 || d==0) {
            cout << "Case " << ++kase << ": " << 1 << ' ' << k1 << ' ' << k1 << endl;
        } else {
            for (short i = (t1-1)>>1; i >= 0; --i) {
                short t = a1[i]; a1[i] = a1[t1-1-i]; a1[t1-1-i] = t;
            }
            for (short i = (t0-1)>>1; i >= 0; --i) {
                short t = a0[i]; a0[i] = a0[t0-1-i]; a0[t0-1-i] = t;
            }
            for (short i=0; i<=n; ++i) dp[t1][i] = 1;
            for (short i=t1-1; i>=0; --i) {
                short ii = min(n-t1+i, a1[i]+d); dp[i][ii+1] = 0;
                for (short j=ii; j>=0; --j) {
                    if (a1[i] == j) {
                        k = dp[i][j] = dp[i][j+1] + dp[i+1][j+1];
                    } else if (j > a1[i]) {
                        if (a0[j-i-1] <= a1[i]+d) {
                            k = dp[i][j] = dp[i][j+1] + dp[i+1][j+1];
                        } else {
                            dp[i][j] = 0;
                        }
                    } else {
                        if (a0[j-i]+d >= a1[i]) {
                            k = dp[i][j] = dp[i][j+1] + dp[i+1][j+1];
                        } else {
                            dp[i][j] = dp[i][j+1];
                        }
                    }
                }
            }
            ULL mini = 0, maxi = 0; short si=0;
            for (short i=0, ii; i<t0; ++i, si = ii+1) {
                ii = max(si, a0[i]-d);
                while (ii-i < t1 && a1[ii-i]+d < a0[i]) {
                    mini = 1 + (mini<<1); ++ii; ++si;
                }
                for (short j=si; j<ii; ++j) mini = 1 + (mini<<1);
                mini <<= 1;
            }
            while (si++ < n) mini = 1 + (mini<<1);
            si=0;
            for (short i=0, ii; i<t1; ++i, si=ii+1) {
                ii = max(si, a1[i]-d);
                while (ii-i < t0 && a0[ii-i]+d < a1[i]) {
                    maxi <<= 1; ++ii; ++si;
                }
                for (short j=si; j<ii; ++j) maxi <<= 1;
                maxi = 1 + (maxi<<1);
            }
            while (si++ < n) maxi <<= 1;
            cout << "Case " << ++kase << ": " << k << ' ' << mini << ' ' << maxi << endl;
        }
    }
    return 0;
}