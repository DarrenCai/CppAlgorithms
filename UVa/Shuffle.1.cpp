/**
 * UVa12174
 * Shuffle的播放记录
 */

#include <iostream>
#include <vector>
using namespace std;

#define min(a,b) (a<b ? a:b)
#define N 100005
int a[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int d; cin >> d;
    while (d--) {
        int s, n, ans=0; cin >> s >> n;
        for (int i=0; i<n; ++i) cin >> a[i];
        int t = (n + s-1) / s; vector<vector<int> > v1(t, vector<int>(s+1, 0)); vector<int> v2(t, 0);
        for (int i=0; i<n; ++i) {
            int p = (i+s) / s - 1; if (++v1[p][a[i]] == 1) ++v2[p];
        }
        vector<bool> used(s+1, false);
        for (int i=0, m=min(s,n); i<m; ++i) {
            if (used[a[i]]) break;
            bool ok = true; used[a[i]] = true;
            for (int j=i; j<n; j+=s) {
                int p = (j+s) / s - 1; if (--v1[p][a[j]] == 0) --v2[p];
                if (p > 0) {
                    if (++v1[p-1][a[j]] == 1) ++v2[p-1];
                    if (v2[p-1] < s) ok = false;
                }
            }
            int p = (n-i-1 + s-1) / s - 1; if (v2[p] < (n-i-1)%s) ok = false;
            if (ok) ++ ans;
        }
        if (s>n && ans==n) ans += s-n;
        cout << ans << endl;
    }
    return 0;
}