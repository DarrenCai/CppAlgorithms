/**
 * UVa11552
 * 最小的块数
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 1010
char s[N]; int d[N][26];

int solve() {
    int n, k; cin >> k >> s; n = strlen(s);
    for (int i=0; i<n; i+=k) {
        sort(s+i, s+i+k);
        int m = unique(s+i, s+i+k) - s;
        for (int j=0; j<26; ++j) {
            int k1 = lower_bound(s+i, s+m, 'a'+j) - s;
            d[i][j] = k1==m || s[k1]>'a'+j ? n : m-i;
            if (i>0 && d[i][j]<n) {
                int (&r)[26] = d[i-k], x = n;
                for (int p=0; p<26; ++p) if (r[p]<n) {
                    int k2 = lower_bound(s+i, s+m, 'a'+p) - s;
                    x = min(x, r[p] - (k2<m && s[k2]=='a'+p && (j!=p || m-i==1)));
                }
                d[i][j] += x;
            }
        }
    }
    int (&r)[26] = d[n-k], ans = n;
    for (int i=0; i<26; ++i) ans = min(ans, r[i]);
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}