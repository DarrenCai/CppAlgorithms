/**
 * UVa1519/LA5913
 * NEERC 2011
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 10005
#define L 42
int s[N*L][26], c[26], f[26], n; long long ans; char w[N][L];

void solve() {
    int t = ans = 0; memset(s[0], 0, sizeof(s[0])); memset(c, 0, sizeof(c)); memset(f, 0, sizeof(f));
    for (int i=0; i<n; ++i) {
        cin >> w[i];
        if (!w[i][1]) if (++f[w[i][0]-'a'] == 1) ++ans; 
        for (int m = strlen(w[i]), j=m-1, x=0; j>=0; --j) {
            int ch = w[i][j]-'a', &r = s[x][ch];
            if (!r) {
                memset(s[r = ++t], 0, sizeof(s[r]));
                if (j+1 < m) ++c[ch];
            }
            x = r;
        }
    }
    memset(s[0], 0, sizeof(s[0]));
    for (int i=0, p=0; i<n; ++i) for (int j=0, x=0; w[i][j]; ++j) {
        int ch = w[i][j]-'a', &r = s[x][ch];
        if (!r) {
            memset(s[r = ++p], 0, sizeof(s[r]));
            ans += t - (j ? c[ch] : 0);
        }
        x = r;
    }
    cout << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n) solve();
    return 0;
}