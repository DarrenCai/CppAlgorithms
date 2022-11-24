/**
 * UVa11361
 * 数字和与倍数
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define M 82
#define N 100000
int s[N], p[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

int solve() {
    int a, b, k, ans = 0; cin >> a >> b >> k;
    if (k > M) return 0;
    int m = upper_bound(p, p+10, a) - p, n = upper_bound(p, p+10, b) - p, c = (n+1)>>1;
    vector<int> e[M][M];
    for (int i=0; i<p[c]; ++i) e[i%k][s[i]%k].push_back(i);
    if (m == n) {
        for (int q=p[m-c], y=a/q, z=b/q, x=y; x<=z; ++x) {
            int r1 = x*q%k, r2 = s[x]%k; const vector<int> &r = e[r1 ? k-r1 : 0][r2 ? k-r2 : 0];
            ans += lower_bound(r.begin(), r.end(), x<z ? q : b-x*q+1)
                    - lower_bound(r.begin(), r.end(), x>y ? 0 : a-x*q);
        }
    } else {
        for (int q=p[n-c], x=p[c]/10, y=b/q; x<=y; ++x) {
            int r1 = x*q%k, r2 = s[x]%k; const vector<int> &r = e[r1 ? k-r1 : 0][r2 ? k-r2 : 0];
            ans += lower_bound(r.begin(), r.end(), x<y ? q : b-x*q+1) - r.begin();
        }
        while (--n > m) for (int q=p[n - (c = (n+1)>>1)], x=p[c]/10; x<p[c]; ++x) {
            int r1 = x*q%k, r2 = s[x]%k;  const vector<int> &r = e[r1 ? k-r1 : 0][r2 ? k-r2 : 0];
            ans += lower_bound(r.begin(), r.end(), q) - r.begin();
        }
        for (int q=p[m - (c = (m+1)>>1)], y=a/q, x=y; x<p[c]; ++x) {
            int r1 = x*q%k, r2 = s[x]%k; const vector<int> &r = e[r1 ? k-r1 : 0][r2 ? k-r2 : 0];
            ans += lower_bound(r.begin(), r.end(), q) - lower_bound(r.begin(), r.end(), x>y ? 0 : a-x*q);
        }
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=0; i<N; ++i) {
        s[i] = 0;
        for (int j=i; j; j/=10) s[i] += j%10;
    }
    short t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}