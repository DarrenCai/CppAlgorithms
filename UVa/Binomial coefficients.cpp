/**
 * UVa1649
 * 二项式系数
 */

#include <iostream>
#include <cmath>
using namespace std;
int ans[100][2];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        long long m; cin >> m; short c = 0;
        for (short k=49; k>1; --k) {
            long double v = m;
            for (short i=2; i<=k; ++i) v *= i;
            int l = k<<1, r = ceil(pow(v, 1.l/k))+k-1; int n = 0;
            while (l <= r && !n) {
                int mid = (l+r) >> 1; long long v = mid-k+1;
                for (int i=2; i<=k; ++i) v = v*(mid-k+i)/i;
                if (v == m) n = mid;
                v>m ? r=mid-1 : l=mid+1;
            }
            if (n) {
                ans[c][0] = n; ans[c++][1] = k;
                if (n > (k<<1)) ans[c][0] = n, ans[c++][1] = n-k;
            }
        }
        cout << c + (m>2 ? 2:1) << endl;
        if (c) cout << '(' << ans[0][0] << ',' << ans[0][1] << ')';
        for (int i=1; i<c; ++i) cout << " (" << ans[i][0] << ',' << ans[i][1] << ')';
        cout << (c>0 ? " (" : "(") << m << ',' << 1 << ')';
        if (m > 2) cout << " (" << m << ',' << m-1 << ')';
        cout << endl;
    }
    return 0;
}