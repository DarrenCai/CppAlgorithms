/**
 * UVa1653
 * 倍数问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 10010
short a[10], s[2][N], c[2], t, l, n;
struct node {short p, c;} d[N][N]; bool visit[N];

void solve() {
    c[0] = l = 0;
    memset(visit, 0, sizeof(visit));
    if (t == 0 || (t==1 && a[0] == 0)) return;
    short c1 = 0, c2 = 0;
    for (short i=a[0] ? 0 : 1; i<t; ++i) {
        short r = a[i]%n;
        if (!visit[r]) {
            d[0][r].p = -1; d[0][r].c = a[i];
            visit[r] = true;
            ++c2;
            s[0][c[0]++] = r;
        }
    }
    while (!visit[0] && c1<c2) {
        c1 = c2;
        short (&ps)[N] = s[l&1], &pc = c[l&1];
        node (&prev)[N] = d[l];
        short (&cs)[N] = s[++l&1], &cc = c[l&1] = 0;
        node (&curr)[N] = d[l];
        for (short i=0; i<pc; ++i) for (short j=0; j<t; ++j) {
            short r = (10l*ps[i]+a[j])%n;
            if (!visit[r]) {
                curr[r].p = ps[i]; curr[r].c = a[j];
                cs[cc++] = r;
                visit[r] = true;
                ++c2;
            }
            if (r == 0) return;
        }
    }
}

void print(const node& node, short c) {
    if (node.p >= 0) print(d[c-1][node.p], c-1);
    if (node.c >= 0) cout << node.c;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short m, kase = 0;
    while (cin >> n >> m) {
        bool f[10] = {false};
        while (m--) {
            short i; cin >> i; f[i] = true;
        }
        t = 0;
        for (short i=0; i<10; ++i) if (!f[i]) a[t++] = i;
        solve();
        if (!visit[0]) {
            cout << "Case " << ++kase << ": -1" << endl;
        } else {
            cout << "Case " << ++kase << ": ";
            print(d[l][0], l);
            cout << endl;
        }
    }
    return 0;
}