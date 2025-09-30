/**
 * UVa1302/LA2417
 * Shanghai 2001
 */

#include <iostream>
using namespace std;

#define M 25
int l[M], r[M], t[M], b[M], f[5], cl[10], cr[10], ct[10], cb[10], m, n, kase = 0; bool vis[M];

bool h(int r, int c) {
    bool ret = true;
    if (c > 0) {
        if (cl[::r[f[c-1]]]-- == 0) ret = false;
        if (r+1 < n) for (int i=0; i<c; ++i) if (ct[b[f[i]]]-- == 0) ret = false;
    }
    if (r > 0) for (int i=c; i<n; ++i) if (ct[b[f[i]]]-- == 0) ret = false;
    int sr = n-r, sl = c > 0 ? sr-1 : sr, sb = r+1 < n ? n : n-c, st = r > 0 ? 0 : n-c;
    for (int i=0; i<10; ++i) {
        if (cl[i] > cr[i]) sl -= cl[i] - cr[i];
        if (cl[i] < cr[i]) sr -= cr[i] - cl[i];
        if (ct[i] > cb[i]) st -= ct[i] - cb[i];
        if (ct[i] < cb[i]) sb -= cb[i] - ct[i];
    }
    if (c > 0) {
        ++cl[::r[f[c-1]]];
        if (r+1 < n) for (int i=0; i<c; ++i) ++ct[b[f[i]]];
    }
    if (r > 0) for (int i=c; i<n; ++i) ++ct[b[f[i]]];
    return ret && sl >= 0 && sr >= 0 && st >= 0 && sb >= 0;
}

bool dfs(int r = 0, int c = 0) {
    if (r == n) return true;
    if (c == n) return dfs(r+1);
    if (h(r, c)) for (int i=0; i<m; ++i) if (!vis[i]) {
        if ((r > 0 && b[f[c]] != t[i]) || (c > 0 && ::r[f[c-1]] != l[i])) continue;
        int e = f[c]; f[c] = i; vis[i] = true; --cl[l[i]]; --cr[::r[i]]; --ct[t[i]]; --cb[b[i]];
        if (dfs(r, c+1)) return true;
        f[c] = e; vis[i] = false; ++cl[l[i]]; ++cr[::r[i]]; ++ct[t[i]]; ++cb[b[i]];
    }
    return false;
}

void solve() {
    m = n*n;
    for (int i=0; i<10; ++i) cl[i] = cr[i] = ct[i] = cb[i] = 0;
    for (int i=0, j=m; i<j; ++i)
        cin >> t[i] >> r[i] >> b[i] >> l[i], vis[i] = false, ++cl[l[i]], ++cr[r[i]], ++ct[t[i]], ++cb[b[i]];
    cout << "Game " << ++kase << (dfs() ? ": Possible" : ": Impossible") << endl << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}