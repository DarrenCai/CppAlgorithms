/**
 * UVa1611
 * 起重机
 */

#include <iostream>
using namespace std;

#define N 10010
short a[N], p[N], step[3*N][2];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        short s = 0, n; cin >> n;
        for (short i=1; i<=n; ++i) cin >> a[i], p[a[i]] = i;
        for (short i=1; i<n; ++i) if (p[i] != i) {
            short pos = p[i];
            if (n+i+1 < (pos<<1)) {
                if (pos == n && (n-i+1)&1) {
                    step[s][0] = n-1; step[s++][1] = n;
                    short v = a[n]; a[n] = a[n-1]; a[n-1] = v;
                    pos = p[v] = n-1; p[a[n]] = n;
                }
                short l = (pos-i+1)>>1; step[s][0] = pos+1 - (l<<1); step[s++][1] = pos;
                for (short k=0; k<l; ++k) {
                    short v = a[pos-k]; a[pos-k] = a[pos-k-l]; a[pos-k-l] = v;
                    p[v] = pos-k-l; p[a[pos-k]] = pos-k;
                }
                if ((pos = pos-l) == i) continue;
            }
            short l = pos - i; step[s][0] = i; step[s++][1] = pos+l-1;
            for (short k=0; k<l; ++k) {
                short v = a[i+k]; a[i+k] = a[i+k+l]; a[i+k+l] = v;
                p[v] = i+k+l; p[a[i+k]] = i+k;
            }
        }
        cout << s << endl;
        for (short i=0; i<s; ++i) cout << step[i][0] << ' ' << step[i][1] << endl;
    }
    return 0;
}