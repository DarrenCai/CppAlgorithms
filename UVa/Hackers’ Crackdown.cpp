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
        int a = (1<<n) - 1, cc = 0, s = 0, ss, m, v;
        for (int i=0; i<n; ++i) {
            ss = 1<<i; cin >> m;
            while (m--) cin >> v, ss |= 1<<v;
            ss == a ? ++cc : c[1<<s++] = ss;
        }
        for (ss=(1<<s)-1, s=1; s<=ss; ++s) {
            c[s] = c[s&(s-1)] | c[s&-s];
            if (d[s] = c[s] == a) for (m=s&(s-1), v=s>>1; m>v; m=s&(m-1)) d[s] = max(d[s], d[s^m]+d[m]);
        }
        cout << "Case " << ++kase << ": " << cc + d[ss] << endl;
    }
    return 0;
}