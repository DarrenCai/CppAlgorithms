/**
 * UVa11213
 * Flipull 游戏
 */

#include <iostream>
using namespace std;

#define T 10000000
#define N 6
int *trie[18*T], g[12], p[T], d[T], n, t, c, ans, kase = 0; short b; bool r[12]; char s[102], ch;
struct node {char s[N][N], c; short b;} q[T];

bool fr(const node &e, int i) {
    q[t] = e;
    char &c = q[t].c; int cc = 0, j;
    for (j=n-1; j>=0; --j) if (e.s[i][j]) {
        if (c == 'M' || e.s[i][j] == c) {
            c = e.s[i][j]; q[t].s[n-1][j] = 0; ++cc;
            for (int k=i+1; k<n; ++k) q[t].s[k-1][j] = e.s[k][j];
        } else {
            q[t].s[i][j] = c; c = e.s[i][j]; break;
        }
    }
    if (j < 0) {
        for (j=i-1; j>=0; --j) if (e.s[j][0]) {
            if (c == 'M' || e.s[j][0] == c) {
                c = e.s[j][0]; ++cc;
                for (int k=j+1; k<n; ++k) q[t].s[k-1][0] = q[t].s[k][0];
                q[t].s[n-1][0] = 0;
            } else {
                q[t].s[j][0] = c; c = e.s[j][0]; break;
            }
        }
    }
    q[t].b -= cc;
    return cc > 0;
}

bool fc(const node &e, int i) {
    q[t] = e;
    char &c = q[t].c; int cc = 0;
    for (int j=n-1; j>=0; --j) if (e.s[j][i]) {
        if (c == 'M' || e.s[j][i] == c) {
            c = e.s[j][i]; q[t].s[j][i] = 0; ++cc;
        } else {
            q[t].s[j][i] = c; c = e.s[j][i]; break;
        }
    }
    q[t].b -= cc;
    return cc > 0;
}

int cvt(char c) {
    return c == 'X' ? 1 : (c == 'O' ? 2 : (c == 'T' ? 3 : (c == '#' ? 4 : 0)));
}

int find(int &o) {
    if (!o) {
        o = ++c;
        if (trie[o] == NULL) trie[o] = new int[5];
        trie[o][0] = trie[o][1] = trie[o][2] = trie[o][3] = trie[o][4] = 0;
    }
    return o;
}

void insert() {
    int r = find(trie[0][cvt(q[t].c)]);
    for (int i=0, m=n-1; i<n; ++i) for (int j=0; j<n; ++j) if (i==m && j==m) {
        int &o = trie[r][cvt(q[t].s[i][j])];
        if (o) return;
        o = ++c; ++t;
    } else r = find(trie[r][cvt(q[t].s[i][j])]);
}

bool ext(int i) {
    for (int j=0; j<12; ++j) if (g[j] >= 0 && (r[j] ? fr(q[i], g[j]) : fc(q[i], g[j]))) {
        p[t] = i; d[t] = j;
        if (q[t].b <= b) return true;
        insert();
    }
    return false;
}

void print(int i) {
    if (p[i]) print(p[i]);
    cout << d[i] + 1;
    i == t ? cout << endl << endl : cout << ' ';
}

void print() {
    cout << "Case " << ++kase << ": " << s << endl << ans << endl;
    print(t);
}

void solve() {
    cin >> b >> q[0].c >> s; q[0].b = n*n; trie[0][1] = trie[0][2] = trie[0][3] = trie[0][4] = c = 0;
    for (int i=n-1; i>=0; --i) for (int j=0; j<n; ++j) cin >> q[0].s[i][j];
    for (int i=0; i<12; ++i) cin >> ch, r[i] = ch=='r', ch == 'X' ? g[i] = -1 : (cin >> g[i], --g[i]);
    for (int h=0, c=t=ans=1; h<c;) {
        if (ext(h)) return print();
        if (++h == c) c = t, ++ans;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    trie[0] = new int[5];
    while (cin >> n && n) solve();
    return 0;
}