/**
 * UVa10214
 * 树林里的树
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define N 2010
#define K 45
bool flag[N]={false}; short g[N][K][K], cnt[N][K]={0};

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short i=2; i<K; ++i) if (!flag[i])
        for (int j=i*i; j<N; j+=i) flag[j] = true;
    for (short i=1; i<N; ++i) if (flag[i]) {
        short m = sqrt(i+.5), n=i;
        for (short j=2; j<=m; ++j) if (n%j == 0) {
            while (n%j == 0) n /= j;
            g[i][1][cnt[i][1]++] = j;
        }
        if (n > 1) g[i][1][cnt[i][1]++] = n;
        if (cnt[i][1] > 1) {
            m=1; for (short j=0; j<cnt[i][1]; ++j) m *= g[i][1][j];
            for (n=g[i][1][0]*g[i][1][1]; n<=m; ++n) if (cnt[n][1] > 1 && m%n == 0)
                g[i][cnt[n][1]][cnt[i][cnt[n][1]]++] = n;
        }
    }
    cout << fixed << setprecision(7);
    int a, b;
    while (cin>>a>>b && a && b) {
        if (a > b) {
            int t = a; a = b; b = t;
        }
        long long s = b+1;
        for (short i=2; i<=a; ++i) {
            s += b;
            if (flag[i]) for (short j=1; j<=cnt[i][1]; ++j) for (short k=cnt[i][j]-1; k>=0; --k)
                j&1 ? s -= b/g[i][j][k] : s += b/g[i][j][k];
            else s -= b/i;
        }
        cout << s/(1.*a*b + .5*a + .5*b) << endl;
    }
    return 0;
}