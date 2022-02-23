/**
 * UVa1169
 * 捡垃圾的机器⼈
 */

#include <iostream>
using namespace std;

#define N 100100
long long r[N], s[N]; int w[N]; struct node {int i; long long d;} q[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t; s[0] = w[0] = q[0].i = q[0].d = 0;
    while (t--) {
        int n, c, head = 0, tail = 0; long long x0 = 0, y0 = 0;
        cin >> c >> n; r[n+1] = s[n+1] = 0;
        for (int i=1; i<=n; ++i) {
            long long x, y; cin >> x >> y >> w[i]; w[i] += w[i-1];
            r[i] = abs(x) + abs(y); s[i] = s[i-1] + abs(x-x0) + abs(y-y0); x0 = x; y0 = y;
        }
        for (int i=1; i<=n; ++i) {
            while (head <= tail) {
                if (w[i] - w[q[head].i] <= c) break;
                ++head;
            }
            long long d = q[head].d + r[i] + r[i+1] + s[i] - s[i+1];
            while (q[tail].d >= d) --tail;
            q[++tail].i = i; q[tail].d = d;
        }
        cout << q[tail].d << endl;
        if (t) cout << endl;
    }
    return 0;
}