/**
 * UVa12086/LA2191
 * 电位计
 * Dhaka 2006
 */

#include <iostream>
using namespace std;

#define N 200100
int a[N], c[N], n, x, y, kase = 0; char s[4];

void update(int i, int k) {
    while (i <= n) c[i] += k, i += i&-i;
}

int query(int i) {
    int s = 0;
    while (i > 0) s += c[i], i -= i&-i;
    return s;
}

void solve() {
    for (int i=1; i<=n; ++i) c[i] = 0;
    for (int i=1; i<=n; ++i) cin >> a[i], update(i, a[i]);
    if (kase++) cout << endl;
    cout << "Case " << kase << ':' << endl;
    while (cin>>s && s[0]!='E') {
        cin >> x >> y;
        if (s[0] == 'S') {
            update(x, y-a[x]); a[x] = y;
        } else cout << query(y) - query(x-1) << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin>>n && n) solve();
    return 0;
}