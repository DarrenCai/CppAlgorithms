/**
 * UVa10829
 * L-空隙子串
 */

#include <iostream>
#include <cstring>
using namespace std;

#define L 100050
char s[L]; int sa[L], rk1[L], rk2[L], c[L], height[L], w[L], d[L][17], n, g, t;

bool eq(const int *y, int i, int j, int w) {
    return y[i]==y[j] && max(i, j) + w < n && y[i+w]==y[j+w];
}

int lcp(int l, int r) {
    int a = min(l, r), b = max(l, r), c = w[b-a+1] - 1;
    return c>0 ? min(min(d[a][c], d[b+1-(1<<c)][c]), height[a+(1<<c)]) : d[a][1];
}

int solve() {
    cin >> g >> s;
    int m = 27, *x = rk1, *y = rk2, t = strlen(s); n = (t<<1) + 1;
    for (int i=0, j=t<<1, k='a'-1; i<t; ++i) s[j-i] = s[i] -= k;
    for (int i=0; i<m; ++i) c[i] = 0;
    for (int i=0; i<n; ++i) ++c[x[i] = s[i]];
    for (int i=1; i<m; ++i) c[i] += c[i-1];
    for (int i=n-1; i>=0; --i) sa[--c[x[i]]] = i;
    for (int k=1; k<n; k<<=1) {
        int p = 0;
        for (int i=n-k; i<n; ++i) y[p++] = i;
        for (int i=0; i<n; ++i) if (sa[i] >= k) y[p++] = sa[i]-k;
        for (int i=0; i<m; ++i) c[i] = 0;
        for (int i=0; i<n; ++i) ++c[x[y[i]]];
        for (int i=1; i<m; ++i) c[i] += c[i-1];
        for (int i=n-1; i>=0; --i) sa[--c[x[y[i]]]] = y[i];
        int *z = x; x = y; y = z;
        p = 1; x[sa[0]] = 0;
        for (int i=1; i<n; ++i) x[sa[i]] = eq(y, sa[i-1], sa[i], k) ? p-1 : p++;
        if (p == n) break;
        m = p;
    }
    for (int i=0, k=0; i<n; ++i) {
        if (x[i] == 0) continue;
        if (k) --k;
        int j = sa[x[i]-1];
        while (max(i, j) + k < n && s[i+k] == s[j+k]) ++k;
        height[x[i]] = k;
    }
    for (int i=1; i<n; ++i) d[i-1][1] = height[i]; 
    for (int k=2; 1<<k <= n; ++k) for (int i=0; i+(1<<k) <= n; ++i)
        d[i][k] = min(min(d[i][k-1], d[i+(1<<k-1)][k-1]), height[i+(1<<k-1)]);
    int ans = 0;
    for (int i=1; (i<<1)+g <= t; ++i) for (int j=0; j<t; j+=i) {
        int k = j+i+g;
        if (k >= t) break;
        if (s[j] != s[k]) continue;
        int c = min(lcp(x[j], x[k]), i) + min(lcp(x[(t<<1)-j], x[(t<<1)-k]), i) - 1;
        ans += max(c-i+1, 0);
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    for (int i=1, j=0; i<L; ++i) {
        if (i >= 1<<j+1) ++j;
        w[i] = i > 1<<j ? j+1 : j;
    }
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case " << kase << ": " << solve() << endl;
    return 0;
}