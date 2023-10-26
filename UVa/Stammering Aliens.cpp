/**
 * UVa12206/LA4513
 * 口吃的外星人
 * SWERC 2009
 */

#include <iostream>
using namespace std;

#define L 40005
char s[L]; int sa[L], rk1[L], rk2[L], c[L], height[L], f[L], q[L], len, ans, n, t;

bool eq(const int *y, int i, int j, int w) {
    return y[i]==y[j] && max(i, j) + w < t && y[i+w]==y[j+w];
}

void solve() {
    cin >> s;
    int m = 26, *x = rk1, *y = rk2;
    for (int i=0; i<m; ++i) c[i] = 0;
    for (t=0; s[t]; ++t) ++c[x[t] = s[t]-'a'], f[t] = 0;
    if (n == 1) {
        cout << t << " 0" << endl;
        return;
    }
    for (int i=1; i<m; ++i) c[i] += c[i-1];
    for (int i=t-1; i>=0; --i) sa[--c[x[i]]] = i;
    for (int k=1; k<t; k<<=1) {
        int p = 0;
        for (int i=t-k; i<t; ++i) y[p++] = i;
        for (int i=0; i<t; ++i) if (sa[i] >= k) y[p++] = sa[i]-k;
        for (int i=0; i<m; ++i) c[i] = 0;
        for (int i=0; i<t; ++i) ++c[x[y[i]]];
        for (int i=1; i<m; ++i) c[i] += c[i-1];
        for (int i=t-1; i>=0; --i) sa[--c[x[y[i]]]] = y[i];
        int *z = x; x = y; y = z;
        p = 1; x[sa[0]] = 0;
        for (int i=1; i<t; ++i) {
            x[sa[i]] = eq(y, sa[i-1], sa[i], k) ? p-1 : p++;
        }
        if (p == t) break;
        m = p;
    }
    for (int i=0, k=0; i<t; ++i) {
        if (x[i] == 0) continue;
        if (k) --k;
        int j = sa[x[i]-1];
        while (max(i+k, j+k)<t && s[i+k] == s[j+k]) ++k;
        height[x[i]] = k;
    }
    for (int i=1, c=0, x=1, head=0, tail=len=0; i<t; ++i) {
        if (height[i] <= len) {
            head = tail = c = 0; x = i+1; continue;
        }
        if (f[i-1] < x) ++c;
        if (f[i] < x) ++c;
        f[i-1] = f[i] = i;
        while (f[x-1] > x) ++x;
        while (c > n) {
            ++x; --c;
            while (f[x-1] > x) ++x;
        }
        while (head<tail && q[head]<x) ++head;
        while (head<tail && height[i] <= height[q[tail-1]]) --tail;
        q[tail++] = i;
        if (c >= n) len = height[q[head]];
    }
    if (len) {
        for (int i=ans=0; i<t; ++i) f[i] = 0;
        for (int i=1, c = 0, x = 1, y = 0; i<t; ++i) {
            if (height[i] < len) {
                c = y = 0; x = i+1; continue;
            }
            y = max(max(y, sa[i-1]), sa[i]);
            if (f[i-1] < x) ++c;
            if (f[i] < x) ++c;
            f[i-1] = f[i] = i;
            if (c >= n) ans = max(ans, y);
        }
    }
    len ? cout << len << ' ' << ans << endl : cout << "none" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin>>n && n) solve();
    return 0;
}