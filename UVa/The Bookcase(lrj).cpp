/**
 * UVa12099
 * 书架
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define max(a, b) (a>b ? a:b)
#define N 80
#define V 1500

struct book {
    short h, w;
    bool operator< (const book& rhs) const {
        return h>rhs.h;
    }
} books[N];
short d[N][V][V]={0}, w[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        short n, wm=0, mj, mk; cin >> n;
        for (short i=0; i<n; ++i) cin >> books[i].h >> books[i].w;
        sort(books, books+n);
        for (short i=0; i<n; ++i) {
            if (books[i].w > wm) wm = books[i].w;
            w[i] = (i>0 ? w[i-1]:0) + books[i].w;
        }
        mj = (w[--n]+wm) / 2; mk = w[n]/3 + wm;
        memset(d, 0, sizeof(d)); d[0][0][0] = books[0].h;
        for (short i=1; i<=n; ++i) for (short j=0; j<=mj; ++j)
            for (short k=0; k<=mk && k<=j+wm && j+k <= w[n]-books[0].w; ++k) if (d[i-1][j][k] > 0) {
                short f = d[i][j][k]>0 ? d[i][j][k] : V;
                d[i][j][k] = min(d[i-1][j][k], f);
                short jj = j+books[i].w, kk = k+books[i].w;
                short dd = d[i-1][j][k] + (j==0 ? books[i].h : 0);
                f = d[i][jj][k]>0 ? d[i][jj][k] : V;
                d[i][jj][k] = min(dd, f);
                dd = d[i-1][j][k] + (k==0 ? books[i].h : 0);
                f = d[i][j][kk]>0 ? d[i][j][kk] : V;
                d[i][j][kk] = min(dd, f);
            }
        int ans = 1e8;
        for (short j=1; j<=mj; ++j) for (short k=1; k<=mk && k<=j+wm && j+k <= w[n]-books[0].w; ++k)
            if (d[n][j][k] > 0) ans = min(ans, int(d[n][j][k])*max(max(j, k), w[n]-j-k));
        cout << ans << endl;
    }
    return 0;
}