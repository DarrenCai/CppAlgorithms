/**
 * UVa714
 * 抄书
 */

#include <iostream>
using namespace std;

#define max(a,b) (a>b ? a:b)
#define N 505
int a[N]={0}, f[N], m, k, mi; long long s;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        cin >> m >> k; s = 0; mi = 0;
        for (int i=0; i<m; ++i) cin >> a[i], s += a[i], mi = max(mi, a[i]);
        long long low = max(mi, (s+k-1)/k), high = s, mid = (low + high) / 2, ss; int k1, j;
        while (low <= high) {
            for (j=m-1, k1=1, ss=0; j>=0; --j) {
                if (ss + a[j] > mid) ++k1, ss = a[j];
                else ss += a[j];
            }
            if (k1 > k) low = mid + 1;
            else high = mid - 1;
            mid = (low + high) / 2;
        }
        for (j=m-1, k1=1, ss=0; j>=0 && k1<k; --j) {
            if (k1 + j < k) {
                f[k1++ -1] = j+1;
            } else if ((ss += a[j]) == low) {
                f[k1++ -1] = j; ss = 0;
            } else if (ss > low) {
                f[k1++ -1] = j+1; ss = a[j];
            }
        }
        cout << a[0];
        for (j=k-2, k1=1; j>=0; --j) {
            while (k1 < f[j]) cout << ' ' << a[k1++];
            cout << " /";
        }
        while (k1 < m) cout << ' ' << a[k1++]; cout << endl;
    }
    return 0;
}