/**
 * UVa12174
 * Shuffle的播放记录
 */

#include <iostream>
#include <vector>
#include <set>
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
        int t = (n + s-1) / s; vector<set<int> > v1(t); vector<multiset<int> > v2(t);
        for (int i=0; i<n; ++i) {
            int p = (i+s) / s - 1; v1[p].insert(a[i]); v2[p].insert(a[i]);
        }
        bool used[N] = {false};
        for (int i=0, m=min(s,n); i<m; ++i) {
            if (used[a[i]]) break;
            bool ok = true; used[a[i]] = true;
            for (int j=i; j<n; j+=s) {
                int p = (j+s) / s - 1;
                if (v2[p].count(a[j]) == 1) v1[p].erase(a[j]);
                v2[p].erase(v2[p].find(a[j]));
                if (p > 0) {
                    v1[p-1].insert(a[j]); v2[p-1].insert(a[j]);
                    if (v2[p-1].size() > v1[p-1].size()) ok = false;
                }
            }
            int p = (n-i-1 + s-1) / s - 1; if (v2[p].size() > v1[p].size()) ok = false;
            if (ok) ++ ans;
        }
        if (s>n && ans==n) ans += s-n;
        cout << ans << endl;
    }
    return 0;
}