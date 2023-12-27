/**
 * UVa11488
 * 超级前缀集合
 */

#include <iostream>
using namespace std;

#define N 50021*202
int ch[N][2], c[N], n, t, ans; char s[203];

void build() {
    cin >> s;
    for (int i=0, x=0; s[i]; ++i) {
        int &r = ch[x][s[i]-'0'];
        r == 0 ? (c[r = ++t] = 1, ch[r][0] = ch[r][1] = 0) : ++c[r];
        ans = max(ans, (i+1)*c[r]);
        x = r;
    }
}

void solve() {
    ans = t = ch[0][0] = ch[0][1] = 0;
    cin >> n;
    while (n--) build();
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}