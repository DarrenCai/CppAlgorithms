/**
 * UVa1451/LA4726
 * 平均值
 * Seoul 2009
 * 关键思路：数形结合，凹形（斜率单调不降)，切点
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100050
int s[N], q[N], n, l;

void solve() {
    cin >> n >> l;
    int a = 0, b = l, t = 0, p = 0;
    for (int i=1; i<=n; ++i) {
        int j = i-l; char c; cin >> c; s[i] = s[i-1] + c-'0';
        if (j <= 0) continue;
        while (p+1<=t && (s[j]-s[q[t]])*(j-q[t-1]) <= (s[j]-s[q[t-1]])*(j-q[t])) --t;
        q[++t] = j;
        while (p+1<=t && (s[i]-s[q[p]])*(i-q[p+1]) <= (s[i]-s[q[p+1]])*(i-q[p])) ++p;
        int v = (s[i]-s[q[p]])*(b-a) - (s[b]-s[a])*(i-q[p]);
        if (v>0 || (v==0 && i-q[p]<b-a)) a = q[p], b = i;
    }
    cout << a+1 << ' ' << b << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int k; cin >> k; q[0] = s[0] = 0;
    while (k--) solve();
    return 0;
}