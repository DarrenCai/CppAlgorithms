/**
 * UVa1169
 * 捡垃圾的机器⼈
 */

#include <iostream>
using namespace std;

#define INF 1000000000000000ll
long long d[110];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
        int x0 = 0, y0 = 0, x, y, n; short c, w;
        cin >> c >> n;
        d[c] = 0; for (short v=0; v<c; ++v) d[v] = INF;
        for (int i=0; i<n; ++i) {
            cin >> x >> y >> w;
            d[c] += x+y;
            short cc = c-w; long long mx = INF;
            for (short v=0; v<cc; ++v) mx = min(mx, d[v] = d[v+w] + abs(x-x0) + abs(y-y0));
            mx = min(mx, d[cc] = d[c]);
            while (++cc < c) d[cc] = INF;
            d[c] = mx + x+y;
            x0 = x; y0 = y;
        }
        cout << d[c] << endl;
        if (t) cout << endl;
    }
    return 0;
}