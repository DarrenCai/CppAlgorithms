/**
 * UVa11107
 * 生命的形式
 * 二分找最大子串的长度
 */

#include <iostream>
using namespace std;

#define N 101
#define L 102000
char s[L], p[N*10]; int sa[L], rk1[L], rk2[L], c[L], height[L], idx[L], f[N], len, n, t, kase = 0;

bool eq(const int *y, int i, int j, int w) {
    return y[i]==y[j] && max(i, j) + w < t && y[i+w]==y[j+w];
}

bool check(int m) {
    int c = 0, h = n>>1;
    for (int i=0; i<n; ++i) f[i] = 0;
    for (int i=1, x=1, y; s[sa[i]]<26; ++i) {
        if (height[i] < m) {
            if (c > h) return true;
            c = 0; x = i+1;
        } else {
            if (f[y = idx[sa[i-1]]] < x) ++c;
            f[y] = i;
            if (f[y = idx[sa[i]]] < x) ++c;
            f[y] = i;
        }
    }
    return c > h;
}

void print() {
    int c = 0, h = n>>1;
    for (int i=0; i<n; ++i) f[i] = 0;
    for (int i=1, x=1, y; s[sa[i]]<=26; ++i) {
        if (height[i] < len) {
            if (c > h) {
                for (int j=0, k=sa[i-1]; j<len; ++j) cout << char(s[j+k]+'a');
                cout << endl;
            }
            c = 0; x = i+1;
        } else {
            if (f[y = idx[sa[i-1]]] < x) ++c;
            f[y] = i;
            if (f[y = idx[sa[i]]] < x) ++c;
            f[y] = i;
        }
    }
}

void solve() {
    if (kase++) cout << endl;
    if (n == 1) {
        cin >> p; cout << p << endl;
        return;
    }
    for (int i=t=len=0; i<n; ++i) {
        cin >> p;
        int l = 0;
        while (p[l]) s[t] = p[l++]-'a', idx[t++] = i;
        s[t] = 26+i; idx[t++] = n; len = max(len, l);
    }
    int m = 26+n, *x = rk1, *y = rk2;
    for (int i=0; i<m; ++i) c[i] = 0;
    for (int i=0; i<t; ++i) ++c[x[i] = s[i]];
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
        for (int i=1; i<t; ++i) x[sa[i]] = eq(y, sa[i-1], sa[i], k) ? p-1 : p++;
        if (p == t) break;
        m = p;
    }
    for (int i=0, k=0; i<t; ++i) {
        if (x[i] == 0) continue;
        if (k) --k;
        int j = sa[x[i]-1];
        while (max(i, j) + k < t && s[i+k] == s[j+k]) ++k;
        height[x[i]] = k;
    }
    int l = 0;
    while (l <= len) {
        int m = (l+len) >> 1;
        check(m) ? l = m+1 : len = m-1;
    }
    if (len) print();
    else cout << '?' << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin>>n && n) solve();
    return 0;
}