/**
 * UVa12345
 * 动态区间不同值
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define M 1000010
#define N 50010
#define S 224
int a[N], b[N], p[N], q[M], nxt[N], pre[N], m, n;

bool cmp(int i, int j) {
    return a[i] < a[j] || (a[i] == a[j] && i < j);
}

bool cmp2(int i, int v) {
    return a[i] < v;
}

bool cmp3(int v, int i) {
    return v < a[i];
}

int get_pre(int x, int y) {
    if (x % S) {
        int h = x - x%S, t = min(h+S, n), r = lower_bound(b+h, b+t, y, cmp2) - b;
        if (r < t && b[r] < x && a[b[r]] == y) {
            while (++r < t && b[r] < x && a[b[r]] == y);
            return b[r-1];
        }
        x = h;
    }
    for (int i = x; i >= S; i -= S) {
        int r = upper_bound(b+i-S, b+i, y, cmp3) - b - 1;
        if (b[r] < x && a[b[r]] == y) return b[r];
    }
    return -1;
}

int get_next(int x, int y) {
    if (++x % S) {
        int h = x - x%S, t = min(h+S, n), r = upper_bound(b+h, b+t, y, cmp3) - b - 1;
        if (b[r] >= x && a[b[r]] == y) {
            while (--r >= h && b[r] >= x && a[b[r]] == y);
            return b[r+1];
        }
        x = t;
    }
    for (int i=x; i<n; i+=S) {
        int t = min(i+S, n), r = lower_bound(b+i, b+t, y, cmp2) - b;
        if (r < t && a[b[r]] == y) return b[r];
    }
    return n;
}

void update_pre(int x, int u) {
    int h = x - x%S, t = min(h+S, n);
    if (p[x] > u) {
        int i = lower_bound(pre+h, pre+t, p[x]) - pre;
        while (i > h && pre[i-1] > u) pre[i] = pre[i-1], --i;
        pre[i] = p[x] = u;
    } else {
        int i = upper_bound(pre+h, pre+t, p[x]) - pre - 1;
        while (i+1 < t && pre[i+1] < u) pre[i] = pre[i+1], ++i;
        pre[i] = p[x] = u;
    }
}

void modify(int x, int y) {
    if (a[x] == y) return;
    int u = get_pre(x, y), v = get_next(x, y), h = x - x%S, t = min(h+S, n);
    int i = lower_bound(b+h, b+t, x, cmp) - b;
    if (a[x] < y) {
        while (i+1 < t && (a[b[i+1]] < y || (a[b[i+1]] == y && b[i+1] < x))) b[i] = b[i+1], ++i;
        b[i] = x;
    } else {
        while (i > h && (a[b[i-1]] > y || (a[b[i-1]] == y && b[i-1] > x))) b[i] = b[i-1], --i;
        b[i] = x;
    }
    if (p[x] >= 0) nxt[p[x]] = nxt[x];
    if (nxt[x] < n) update_pre(nxt[x], p[x]);
    if (u >= 0) nxt[u] = x;
    if (v < n) update_pre(v, x);
    update_pre(x, u); nxt[x] = v; a[x] = y;
}

void query(int x, int y) {
    int cnt = 0, l = x, r = y-1;
    for (int i = min(l-l%S+S, min(y, n)); l<i; ++l) if (p[l] < x) ++cnt;
    for (int i = max(r-r%S, l); r >= i; --r) if (p[r] < x) ++cnt;
    for (int i=l; i<r; i+=S) cnt += lower_bound(pre+i, pre+i+S, x) - pre - i;
    cout << cnt << endl;
}

void solve() {
    cin >> n >> m; memset(q, -1, sizeof(q));
    for (int i=0; i<n; ++i) {
        cin >> a[i]; b[i] = i;
        if (q[a[i]] >= 0) nxt[q[a[i]]] = i;
        pre[i] = p[i] = q[a[i]]; nxt[i] = n; q[a[i]] = i;
        if (i > 0 && i%S == 0) sort(pre+i-S, pre+i), sort(b+i-S, b+i, cmp);
    }
    int h = n - (n%S ? n%S : S);
    sort(pre+h, pre+n); sort(b+h, b+n, cmp);
    while (m--) {
        char ch; int x, y; cin >> ch >> x >> y;
        ch == 'M' ? modify(x, y) : query(x, y);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}