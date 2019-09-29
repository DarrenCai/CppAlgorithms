/**
 * UVa12265
 * 贩卖土地
 */

#include <iostream>
using namespace std;

#define N 1000
char s[N][N+1]; short f[N][2];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short k; cin>>k;
    while (k--) {
        short n, m, h[N]={0}; int ans[1+(N<<2)]={0};
        cin >> n >> m; for (short i=0; i<n; ++i) cin >> s[i];
        for (short r=0; r<n; ++r) {
            for (short c=0; c<m; ++c) s[r][c]=='.' ? ++h[c] : h[c] = 0;
            for (short t=0, c=0; c<m; ++c) {
                if (s[r][c]=='.') {
                    if (t==0) {
                        f[t][0] = c; f[t++][1] = h[c];
                        ++ans[(h[c]+1)<<1];
                    } else {
                        if (f[t-1][1] > h[c]) {
                            f[t-1][1] = h[c];
                            while(t>1 && f[t-2][1]>=h[c]) f[--t-1][1]=h[c];
                            if (t>1 && f[t-1][1]==h[c] && f[t-1][1]-f[t-1][0] < f[t-2][1]-f[t-2][0]) --t;
                        }
                        if (h[c]-c > f[t-1][1]-f[t-1][0]) {
                            f[t][0] = c; f[t++][1] = h[c];
                        }
                        ++ans[(c-f[t-1][0] + 1 + f[t-1][1])<<1];
                    }
                } else t=0;
            }
        }
        for (short i=4, l=(n+m)<<1; i<=l; ++i) if (ans[i]) cout << ans[i] << " x " << i << endl;
    }
    return 0;
}