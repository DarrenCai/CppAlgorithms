/**
 * UVa11213
 * Flipull 游戏
 */

#include <iostream>
using namespace std;

#define T 117649 // 7^6
#define N 6
short ans[N*N], d[T], e[N], g[12], m, n, b, t, kase = 0; bool r[12]; char s[102], ch;
const int p[] = {1, 7, 49, 343, 2401, 16807}; struct node {char s[N][N], c;} q[N*N+1];

void dp() {
    int v = 0; m = n*n;
    for (short i=0; i<n; ++i) v += n*p[i];
    for (int x=0; x<v; ++x) {
        int y = x; short s = 0; bool f = false;
        for (short i=0; i<n; ++i, y /= 7) {
            e[i] = y % 7;
            if (e[i] > n) {
                f = true; break;
            }
            s += e[i];
        }
        if (f) continue;
        if (s <= b) {
            d[x] = 0; continue;
        }
        d[x] = m;
        for (short i=0; i<12; ++i) if (g[i] >= 0) if (r[i]) {
            y = x - min(int(e[0]), g[i]+1);
            for (short j=1; j<n; ++j) if (e[j] > g[i]) y -= p[j];
            d[x] = min(d[x], short(d[y]+1));
        } else if (e[g[i]]) d[x] = min(d[x], short(d[x - e[g[i]] * p[g[i]]] + 1));
    }
}

bool fr(const node &e, node &a, short i) {
    a = e; char &c = a.c; short cc = 0, j;
    for (j=n-1; j>=0; --j) if (e.s[i][j]) {
        if (c == 'M' || e.s[i][j] == c) {
            c = e.s[i][j]; a.s[n-1][j] = 0; ++cc;
            for (short k=i+1; k<n; ++k) a.s[k-1][j] = e.s[k][j];
        } else {
            a.s[i][j] = c; c = e.s[i][j]; break;
        }
    }
    if (j < 0) {
        for (j=i-1; j>=0; --j) if (e.s[j][0]) {
            if (c == 'M' || e.s[j][0] == c) {
                c = e.s[j][0]; ++cc;
                for (short k=j+1; k<n; ++k) a.s[k-1][0] = a.s[k][0];
                a.s[n-1][0] = 0;
            } else {
                a.s[j][0] = c; c = e.s[j][0]; break;
            }
        }
    }
    return cc > 0;
}

bool fc(const node &e, node &a, short i) {
    a = e; char &c = a.c; short cc = 0;
    for (short j=n-1; j>=0; --j) if (e.s[j][i]) {
        if (c == 'M' || e.s[j][i] == c) {
            c = e.s[j][i]; a.s[j][i] = 0; ++cc;
        } else {
            a.s[j][i] = c; c = e.s[j][i]; break;
        }
    }
    return cc > 0;
}

short h(const node &a) {
    int x = 0;
    for (short i=0, k; i<n; ++i) {
        for (k=0; k<n; ++k) if (!a.s[k][i]) break;
        x += k * p[i];
    }
    return d[x];
}

bool IDAStar(short s = 0) {
    if (s == t) return h(q[s]) == 0;
    node &e = q[s+1];
    for (short i=0; i<12; ++i) if (g[i] >= 0 && (r[i] ? fr(q[s], e, g[i]) : fc(q[s], e, g[i])) && s + h(e) < t) {
        ans[s+1] = i;
        if (IDAStar(s+1)) return true;
    }
    return false;
}

void print() {
    cout << "Case " << ++kase << ": " << s << endl << t << endl;
    for (short i=1; i<t; ++i) cout << ans[i]+1 << ' ';
    cout << ans[t]+1 << endl << endl;
}

void solve() {
    cin >> b >> q[0].c >> s;
    for (short i=n-1; i>=0; --i) for (short j=0; j<n; ++j) cin >> q[0].s[i][j];
    for (short i=0; i<12; ++i) cin >> ch, r[i] = ch=='r', ch == 'X' ? g[i] = -1 : (cin >> g[i], --g[i]);
    dp();
    for (t=1; t<m; ++t) if (IDAStar()) return print();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}