/**
 * UVa1611
 * 起重机
 */

#include <iostream>
using namespace std;

#define N 10010
#define M 140000
short a[N], step[M][2];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        int s = 0; short n; cin >> n;
        for (short i=0; i<n; ++i) cin >> a[i];
        while (n) for (short i=0; i<n; ++i) if (a[i] == n && i < --n) {
            for (short l, j=i; j<n; j+=l) {
                l = (n+1-j) >> 1;
                step[s][0] = j+1;
                step[s++][1] = j+(l<<1);
                for (short k=0; k<l; ++k) {
                    short v = a[j+k];
                    a[j+k] = a[j+k+l];
                    a[j+k+l] = v;
                }
            }
            break;
        }
        cout << s << endl;
        for (int i=0; i<s; ++i) cout << step[i][0] << ' ' << step[i][1] << endl;
    }
    return 0;
}