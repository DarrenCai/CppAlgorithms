/**
 * UVa10570
 * 外星人聚会
 */

#include <iostream>
using namespace std;

#define abs(x) (x>0 ? x : -(x))
#define N 510
short n, mini, a[N], b[N], p[N];

void solve(short s, bool inc) {
    short m = 0;
    for (short i=0; i<n; ++i) p[b[i] = a[i]] = i;
    for (short i=0; i<n; ++i) {
        short v = (i - s + n) % n;
        if (!inc && i!=s) v = n-v;
        if (p[v] != i) {
            p[b[i]] = p[v];
            b[p[v]] = b[i];
            p[v] = i;
            b[i] = v;
            if (++m >= mini) return;
        }
    }
    mini = m;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) {
        for (short i=0; i<n; ++i) cin >> a[i], --a[i];
        bool ok = true;
        for (short i=0; i<n; ++i) {
            short d1 = abs(a[i]-a[(n+i-1) % n]), d2 = abs(a[i]-a[(i+1) % n]);
            if ((d1!=1 && d1!=n-1) || (d2!=1 && d2!=n-1)) {
                ok = false; break;
            }
        }
        if (ok) {
            cout << 0 << endl;
        } else {
            mini = n-1;
            for (short i=0; i<n; ++i) {
                solve(i, false);
                if (mini == 1) break;
                solve(i, true);
                if (mini == 1) break;
            }
            cout << mini << endl;
        }
    }
    return 0;
}