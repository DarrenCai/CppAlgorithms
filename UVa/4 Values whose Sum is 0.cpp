/**
 * UVa1152
 * 和为0的4个值
 */

#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main()
{
    int a[4010], b[4010], c[4010], d[4010]; short t, n; cin >> t;
    while (t--) {
        cin >> n; for (short i=0; i<n; ++i) cin >> a[i] >> b[i] >> c[i] >> d[i];
        sort(a, a+n); sort(b, b+n); sort(c, c+n); sort(d, d+n);
        int max1 = a[n-1] + b[n-1], min1 = a[0] + b[0], max2 = c[n-1] + d[n-1], min2 = c[0] + d[0];
        unordered_map<int, int> m; int r = 0;
        for (short i=0; i<n; ++i) {
            for (short j=0; j<n; ++j) {
                int s = a[i] + b[j];
                if (s + min2 > 0) break;
                if (s + max2 >= 0) m.count(s) ? ++m[s] : m[s] = 1;
            }
        }
        for (short i=0; i<n; ++i) {
            for (short j=0; j<n; ++j) {
                int s = -c[i] - d[j];
                if (min1 > s) break;
                if (max1 >= s && m.count(s)) r += m[s];
            }
        }
        cout << r << endl;
        if (t) cout << endl;
    }
    return 0;
}