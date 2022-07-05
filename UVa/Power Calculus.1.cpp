/**
 * UVa1374/LA3621
 * 快速幂计算
 */

#include <iostream>
using namespace std;

#define M 20
short a[M], n, ans;

bool iddfs(short v = 1, short m = 1, short d = 0) {
    if (d == ans) return v == n;
    if (m << (ans-d) < n) return false;
    for (short i=0; i<=d; ++i) {
        short v1 = v + a[i];
        if (m<n || v1<=n) {
            a[d+1] = v1;
            if (iddfs(v1, max(m, v1), d+1)) return true;
        }
        v1 = abs(v - a[i]);
        if (v1>0 && (m<n || v1<=n)) {
            a[d+1] = v1;
            if (iddfs(v1, max(m, v1), d+1)) return true;
        }
    }
    return false;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    a[0] = 1;
    while (cin>>n && n) {
        for (ans=0; !iddfs(); ++ans);
        cout << ans << endl;
    }
    return 0;
}