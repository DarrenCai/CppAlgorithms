/**
 * UVa242
 * 邮票和信封
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 10
#define M 1000
short s, d[M], c, ans[N], n, cur[N], m;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>s && s) {
        c = 0; n = N+1;
        short t; cin >> t;
        while (t--)  {
            cin >> m; for (short i=0; i<m; ++i) cin >> cur[i];
            memset(d, -1, sizeof(d)); d[0] = 0; short cc=0;
            for (short i=1; i<M; ++i) {
                for (short j=0, ii; j<m && cur[j]<=i; ++j)
                    if (d[ii=i-cur[j]]>=0 && d[ii]<s && (d[i]<0 || d[ii]+1 < d[i])) d[i] = d[ii]+1;
                if (d[i] < 0) {
                    cc = i-1;
                    break;
                }
            }
            if (cc>c || (cc==c && m<n)) c=cc, n=m, memcpy(ans, cur, sizeof(ans));
            else if (cc == c && m==n) {
                bool ok = false;
                for (short i=n-1; i>=0; --i) {
                    if (cur[i] > ans[i]) break;
                    if (cur[i] < ans[i]) {
                        ok = true;
                        break;
                    }
                }
                if (ok) memcpy(ans, cur, sizeof(ans));
            }
        }
        cout << "max coverage =" << (c > 999 ? "" : (c>99 ? " " : (c>9 ? "  " : "   "))) << c << " :";
        for (short i=0; i<min(n, short(N)); ++i)
            cout << (ans[i]>99 ? "" : (ans[i]>9 ? " " : "  ")) << ans[i];
        cout << endl;
    }
    return 0;
}