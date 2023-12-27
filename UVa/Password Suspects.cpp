/**
 * UVa1076/LA4126
 * 破解密码
 * Final 2008
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 10
#define N 27
#define L 13
#define C 26
struct node {int ch[C], val, last, f;} s[M*L];
int q[M*L], m, n, t, kase = 0; long long d[N][M*L][1<<M]; char p[M][L], a[N];

int ss(int x) {
    return x ? 1 << (s[x].val-1) | ss(s[x].last) : 0;
}

long long dfs(int c, int u, int f) {
    long long &r = d[c][u][f];
    if (r >= 0) return r;
    r = 0;
    if (f == (1<<m)-1) {
        r = 1; while (c++ < n) r *= 26;
    } else if (c < n) for (int i=0; i<C; ++i) {
        int v = s[u].ch[i];
        if (s[v].val) r += dfs(c+1, v, f | ss(v));
        else if (s[v].last) r += dfs(c+1, v, f | ss(s[v].last));
        else r += dfs(c+1, v, f);
    }
    return r;
}

void print(int c, int u, int f) {
    if (f == (1<<m)-1) {
        if (c == n) {
            cout << a << endl;
        } else for (int i=0; i<C; ++i) a[c] = 'a'+i, print(c+1, s[u].ch[i], f);
    } else if (c < n) for (int i=0; i<C; ++i) {
        int v = s[u].ch[i], ff = s[v].val ? f | ss(v) : (s[v].last ? f | ss(s[v].last) : f);
        if (d[c+1][v][ff]) a[c] = 'a'+i, print(c+1, v, ff);
    }
}

bool dup(int i) {
    for (int j=0; j<i; ++j) if (strcmp(p[j], p[i]) == 0) return true;
    return false;
}

void solve() {
    memset(s, t = 0, sizeof(node)); memset(d, -1, sizeof(d));
    for (int i=0, x; i<m; ++i) {
        cin >> p[i];
        if (dup(i)) {
            --i; --m; continue;
        }
        for (int j=x=0; p[i][j]; ++j) {
            int &r = s[x].ch[p[i][j]-'a'];
            if (!r) memset(s + (r = ++t), 0, sizeof(node));
            x = r;
        }
        s[x].val = i+1;
    }
    for (int i=0; i<C; ++i) if (!s[0].ch[i]) s[0].ch[i] = ++t, memset(s+t, 0, sizeof(node));
    int head = 0, tail = 0;
    for (int i=0; i<C; ++i) q[tail++] = s[0].ch[i];
    while (head < tail) {
        int x = q[head++];
        for (int i=0; i<C; ++i) {
            int &u = s[x].ch[i];
            if (!u) {
                u = s[s[x].f].ch[i];
                continue;
            }
            q[tail++] = u;
            int &f = s[u].f = s[s[x].f].ch[i];
            s[u].last = s[f].val ? f : s[f].last;
        }
    }
    cout << "Case " << ++kase << ": " << dfs(0, 0, 0) << " suspects" << endl;
    if (d[0][0][0] <= 42) a[n] = 0, print(0, 0, 0);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin>>n>>m && n) solve();
    return 0;
}