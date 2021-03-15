/**
 * UVa10375
 * 选择与除法
 */

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#define N 110
short prim[40*N], c[40*N], t=0;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    const short M = N*N+1; bool f[M] = {0};
    for (short i=2; i<=N; ++i) if (!f[i]) for (short j=i*i; j<M; j+=i) f[j] = true;
    for (short i=2; i<M; ++i) if (!f[i]) prim[t++] = i;
    cout << fixed << setprecision(5);
    short p, q, r, s;
    while (cin >> p >> q >> r >> s) {
        memset(c, 0, sizeof(c));
        if (q > p>>1) q=p-q;
        if (s > r>>1) s=r-s;
        for (short i=1; i<=q; ++i) {
            for (short v=i, j=0; v>1 && j<t && prim[j]<=v;) {
                if (v%prim[j] == 0) {
                    -- c[j]; v /= prim[j];
                } else ++j;
            }
            for (short v=p-i+1, j=0; v>1 && j<t && prim[j]<=v;) {
                if (v%prim[j] == 0) {
                    ++ c[j]; v /= prim[j];
                } else ++j;
            }
        }
        for (short i=1; i<=s; ++i) {
            for (short v=i, j=0; v>1 && j<t && prim[j]<=v;) {
                if (v%prim[j] == 0) {
                    ++ c[j]; v /= prim[j];
                } else ++j;
            }
            for (short v=r-i+1, j=0; v>1 && j<t && prim[j]<=v;) {
                if (v%prim[j] == 0) {
                    -- c[j]; v /= prim[j];
                } else ++j;
            }
        }
        double ans = 1.0;
        for (short i=0; i<t; ++i) {
            if (c[i] > 0) {
                for (short j=c[i]; j>0; --j) ans *= prim[i];
            } else if (c[i] < 0) {
                for (short j=c[i]; j<0; ++j) ans /= prim[i];
            }
        }
        cout << ans << endl;
    }
    return 0;
}