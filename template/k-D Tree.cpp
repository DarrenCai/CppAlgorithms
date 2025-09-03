/**
 * k-D Tree 模板
 * 这里以 k=2 的区间最大值查询为例
 * https://oi-wiki.org/ds/kdt/
 */

#include <algorithm>
using namespace std;

#define N 100100
int a[N], x[N], y[N], dat[N], lc[N], rc[N], x1[N], x2[N], y1[N], y2[N], v[N], p[N], n, t;

bool cmpx(int i, int j) {
    return x[i] < x[j];
}

bool cmpy(int i, int j) {
    return y[i] < y[j];
}

void update(int o, int ch) {
    v[o] = max(v[o], v[ch]);
    x1[o] = min(x1[o], x1[ch]); x2[o] = max(x2[o], x2[ch]);
    y1[o] = min(y1[o], y1[ch]); y2[o] = max(y2[o], y2[ch]);
}

// 区间是[l,r)
void build(int& o, int l, int r, int d = 0) {
    o = ++t; lc[o] = rc[o] = 0;
    if (l+1 < r) {
        int m = (l+r)>>1; nth_element(a+l, a+m, a+r, d&1 ? cmpy : cmpx);
        p[o] = a[m]; v[o] = dat[a[m]]; x1[o] = x2[o] = x[a[m]]; y1[o] = y2[o] = y[a[m]];
        build(lc[o], l, m, d^1); update(o, lc[o]);
        if (m+1 < r) build(rc[o], m+1, r, d^1), update(o, rc[o]);
    } else p[o] = a[l], v[o] = dat[a[l]], x1[o] = x2[o] = x[a[l]], y1[o] = y2[o] = y[a[l]];
}

/* 这里以区间查询为例,复杂度O(n^1/2) */
int query(int o, int l, int r, int xl, int yl, int xr, int yr) {
    if (x1[o] >= xl && x2[o] <= xr && y1[o] >= yl && y2[o] <= yr) return v[o];
    int ans = -inf, m = (l+r)>>1;
    if (x[p[o]] >= xl && x[p[o]] <= xr && y[p[o]] >= yl && y[p[o]] <= yr) ans = dat[p[o]];
    if (lc[o] && max(x1[lc[o]], xl) <= min(x2[lc[o]], xr) && max(y1[lc[o]], yl) <= min(y2[lc[o]], yr))
        ans = max(ans, query(lc[o], l, m-1, xl, yl, xr, yr));
    if (rc[o] && max(x1[rc[o]], xl) <= min(x2[rc[o]], xr) && max(y1[rc[o]], yl) <= min(y2[rc[o]], yr))
        ans = max(ans, query(rc[o], m+1, r, xl, yl, xr, yr));
    return ans;
}

void solve() {
    // 读入数据后建树
    int s = t = 0; build(s, 1, n+1);
    // 查询区间 x1, y1, x2, y2
    int xl, yl, xr, yr;
    int ans = query(1, 1, n, xl, yl, xr, yr);
}