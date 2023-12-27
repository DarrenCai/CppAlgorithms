/**
 * UVa1470/LA4975
 * 魔法阵
 * CERC 2010
 */

#include <iostream>
using namespace std;

#define L 600060
char str[L>>1], s[L]; int r[L], n;

int solve() {
    cin >> str;
    n = 2; s[0] = '@'; s[1] = '#';
    for (int i=0; str[i]; ++i) s[n++] = str[i], s[n++] = '#';
    s[n] = '\0';
    int ans = 0;
    for (int i=1, mx=0, id=0; i<n; ++i) {
        if (i < mx) r[i] = min(r[(id<<1) - i], mx - i);
        else r[i] = 1;
        while (s[i + r[i]] == s[i - r[i]]) {
            if (s[i] == '#' && (r[i]&3) == 0 && r[i-(r[i]>>1)] >= r[i]>>1) ans = max(ans, r[i]);
            r[i]++;
        }
        if (i + r[i] > mx) mx = i + r[i], id = i;
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}