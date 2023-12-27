/**
 * UVa1385/LA3703
 * NEERC 2006
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 21420
#define N 103
int s[M][10], f[M], n, t, kase = 0; char p[N][22], a[12], b[12];

bool empty(int x) {
    for (int i=0; i<10; ++i) if (s[x][i]) return false;
    return true;
}

void set(int &x, int i) {
    if (!x) {
        memset(s[x = ++t], 0, sizeof(s[x])); f[x] = i; return;
    }
    if (f[x]) return;
    if (empty(x)) f[x] = i;
    else for (int j=0; j<10; ++j) set(s[x][j], i);
}

void seta(int j, int &x, int i) {
    if (!x) memset(s[x = ++t], 0, sizeof(s[x])), f[x] = 0;
    if (f[x]) return;
    for (int t=++j; ; ++t) {
        if (!a[t]) {
            set(x, i); return;
        }
        if (a[t] > '0') break;
    }
    for (int t=a[j]-'0'+1; t<10; ++t) set(s[x][t], i);
    seta(j, s[x][a[j]-'0'], i);
}

void setb(int j, int &x, int i) {
    if (!x) memset(s[x = ++t], 0, sizeof(s[x])), f[x] = 0;
    if (f[x]) return;
    for (int t=++j; ; ++t) {
        if (!b[t]) {
            set(x, i); return;
        }
        if (b[t] < '9') break;
    }
    for (char c='0'; c<b[j]; ++c) set(s[x][c-'0'], i);
    setb(j, s[x][b[j]-'0'], i);
}

void add(int i) {
    cin >> a >> b >> b >> p[i];
    int m = strlen(b), k = strlen(a) - m, q = 0, j;
    for (j=0; j<k; ++j) {
        if (f[q]) return;
        int &r = s[q][a[j]-'0'];
        if (!r) memset(s[r = ++t], 0, sizeof(s[r])), f[r] = 0;
        q = r;
    }
    for (j=0; j<m; ++j) {
        if (f[q]) return;
        if (a[j+k] != b[j]) break;
        int &r = s[q][b[j]-'0'];
        if (!r) memset(s[r = ++t], 0, sizeof(s[r])), f[r] = 0;
        q = r;
    }
    if (f[q]) return;
    for (int t=j; t<=m; ++t) {
        if (t == m) {
            if (q) set(q, i);
            else for (int j=0; j<10; ++j) set(s[0][j], i);
            return;
        }
        if (a[t+k]!='0' || b[t]!='9') break;
    }
    for (char c=a[j+k]+1; c<b[j]; ++c) set(s[q][c-'0'], i);
    seta(j+k, s[q][a[j+k]-'0'], i); setb(j, s[q][b[j]-'0'], i);
}

int merge(int x) {
    if (f[x]) return f[x];
    int r = 0;
    for (int i=0; i<10; ++i) {
        if (s[x][i]) {
            int y = merge(s[x][i]);
            if (y < 0) r = -1;
            if (r < 0) continue;
            if (y == 0) {
                if (r) r = -1;
            } else if (r) {
                if (r!=y && strcmp(p[r], p[y])) r = -1;
            } else r = y;
        } else r = -1;
    }
    if (r > 0) f[x] = r;
    return r;
}

int dfs(int x) {
    if (f[x]) return strcmp(p[f[x]], "invalid") ? 1 : 0;
    int c = 0;
    for (int i=0; i<10; ++i) if (s[x][i]) c += dfs(s[x][i]);
    return c;
}

void dfs(int x, int t) {
    if (f[x]) {
        if (strcmp(p[f[x]], "invalid")) a[t] = 0, cout << a << ' ' << p[f[x]] << endl;
        return;
    }
    for (int i=0; i<10; ++i) if (s[x][i]) a[t] = '0'+i, dfs(s[x][i], t+1);
}

void solve() {
    if (kase++) cout << endl;
    memset(s[0], f[t = 0] = 0, sizeof(s[0]));
    for (int i=1; i<=n; ++i) add(i);
    for (int i=0; i<10; ++i) if (s[0][i]) merge(s[0][i]);
    cout << dfs(0) << endl;
    dfs(0, 0);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n) solve();
    return 0;
}