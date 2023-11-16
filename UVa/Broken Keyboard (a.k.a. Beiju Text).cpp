/**
 * UVa11988
 * 破损的键盘（又名：悲剧文本）
 */

#include <iostream>
using namespace std;

#define N 50025
struct {int l, r;} q[N<<1]; char s[N<<1];

void solve() {
    int head = N, tail = N-1, l, n, f = 0;
    for (n=l=0; s[n]; ++n) if (s[n]=='[' || s[n]==']') {
        if (l < n) q[f ? --head : ++tail].l = l, q[f ? head : tail].r = n;
        f = s[n]=='['; l = n+1;
    }
    if (l < n) q[f ? --head : ++tail].l = l, q[f ? head : tail].r = n;
    while (head <= tail) for (int i=q[head].l, j=q[head++].r; i<j; ++i) cout << s[i];
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> s) solve();
    return 0;
}