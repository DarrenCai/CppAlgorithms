/**
 * UVa1450
 * 机场
 */

#include <iostream>
using namespace std;

#define N 5020
int d[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        int n, a, b, ta = 0, tb = 0, c = 0;
        cin >> n >> a >> b;
        d[0] = max(max(a, b)-1, 0);
        for (int i=1; i<n; ++i) {
            int ai, bi; cin >> ai >> bi;
            int x = min(min(a, ta+1), i);
            tb = min(min(b, tb+1), i);
            c = min(min(a+b, c+1), i);
            a += ai; b += bi;
            for (int j=x; j>=0; --j) {
                int dd = j>ta ? d[j-1] : (j>0 ? min(d[j], d[j-1]) : d[0]);
                d[j] = max(max(a-j, b-min(c-j, tb))-1, dd);
            }
            ta = x;
        }
        int ans = d[0];
        for (int i=1; i<=ta; ++i) ans = min(ans, d[i]);
        cout << ans << endl;
    }
    return 0;
}