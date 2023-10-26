/**
 * UVa12206/LA4513
 * 口吃的外星人
 * SWERC 2009
 * 基于哈希值的LCP算法
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define L 40005
char s[L]; int rnk[L], m, n, p; unsigned long long h[L], hs[L], pow[L], x = 123;

bool cmp(const int a, const int b) {
    return hs[a] != hs[b] ? hs[a] < hs[b] : a < b;
}

bool check(int l) {
    int t = m-l+1; p = -1;
    for (int i=0; i<t; ++i) rnk[i] = i, hs[i] = h[i] - h[i+l]*pow[l];
    sort(rnk, rnk+t, cmp);
    for (int i=0, c; i<t; ++i) {
        if (i==0 || hs[rnk[i]] != hs[rnk[i-1]]) c= 0;
        if (++c >= n) p = max(p, rnk[i]);
    }
    return p >= 0;
}

void solve() {
    cin >> s;
    m = strlen(s); h[m] = 0;
    for (int i=m-1; i>=0; --i) h[i] = h[i+1]*x + s[i]-'a';
    if (!check(1)) {
        cout << "none" << endl;
    } else {
        int l = 1, r = m;
        while (l <= r) {
            int x = (l+r) >> 1;
            check(x) ? l = x+1 : r = x-1;
        }
        check(r);
        cout << r << ' ' << p << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    pow[0] = 1; for (int i=1; i<L; ++i) pow[i] = pow[i-1]*x;
    while (cin>>n && n) solve();
    return 0;
}