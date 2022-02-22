/**
 * UVa11825
 * ⿊客的攻击
 */

#include <iostream>
using namespace std;

#define N 16
int c[1<<N], d[1<<N], n;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int kase = c[0] = d[0] = 0;
    while (cin>>n && n) {
        int a = (1<<n) - 1, m, v;
        for (int i=0; i<n; ++i) {
            int &ref = c[1<<i] = 1<<i;
            cin >> m; while (m--) cin >> v, ref |= 1<<v;
        }
        for (int s=1; s<=a; ++s) {
            c[s] = c[s&(s-1)] | c[s&-s]; d[s] = c[s] == a;
            for (int ss=s; ss; ss=s&(ss-1)) d[s] = max(d[s], d[s^ss]+d[ss]);
        }
        cout << "Case " << ++kase << ": " << d[a] << endl;
    }
    return 0;
}