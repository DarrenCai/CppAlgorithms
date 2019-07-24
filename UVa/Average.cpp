/**
 * UVa1451
 * 平均值
 */

#include <iostream>
using namespace std;

#define N 100005
int s[N]={0}, a[N]={0}, n, l; char d[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int k; cin >> k;
    while (k--) {
        cin >> n >> l >> d;
        for (int i=0; i<n; ++i) s[i+1] = s[i] + d[i] - '0';
        int t = 0, e = l, m = 1, ss = 0;
        for (int i=l+1; i<=n; ++i) {
            int j = i-l;
            while (m>1 && (s[a[m-1]]-s[a[m-2]])*(j-a[m-2]) > (s[j]-s[a[m-2]])*(a[m-1]-a[m-2])) if (ss > --m) ss = m;
            a[m++] = j;
            if (s[i] == s[i-1]) continue;
            while (ss+1<m && (s[i]-s[a[ss+1]])*(i-a[ss]) >= (s[i]-s[a[ss]])*(i-a[ss+1])) ++ss;
            int p = (s[i]-s[a[ss]]) * (e - t), q = (s[e]-s[t]) * (i-a[ss]);
            if (p>q || (p==q && i-a[ss] < e-t)) t = a[ss], e = i;
        }
        cout << t+1 << ' ' << e << endl;
    }
    return 0;
}