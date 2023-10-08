/**
 * UVa1160/LA3644
 * 易爆物
 * SWERC 2006
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 100005
int f[N], a, b;

int find(int x) {
    return f[x] = f[x]==x || f[x]<0 ? x : find(f[x]);
}

void solve() {
    memset(f, -1, sizeof(f));
    int t = 0;
    while (a > -1) {
        cin >> b;
        int u = find(a), v = find(b);
        u == v ? ++t : f[u] = v;
        cin >> a;
    }
    cout << t << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin >> a) solve();
    return 0;
}