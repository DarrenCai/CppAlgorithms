/**
 * UVa1358/LA3490
 * 生成器
 * Hangzhou 2005
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 26
#define L 15
int ch[L][N], f[L], q[N*L], n, t; char s[L]; long long a[L][L];

long long solve() {
    cin >> n >> s; memset(a, 0, sizeof(a)); memset(ch[0], f[t = 0] = 0, sizeof(ch[0]));
    for (int i=0, x=0; s[i]; ++i) {
        int &r = ch[x][s[i]-'A'];
        if (!r) memset(ch[r = ++t], 0, sizeof(ch[0])), f[r] = 0;
        x = r;
    }
    int head = 0, tail = 1; q[0] = 1;
    while (head < tail) {
        int x = q[head++];
        for (int i=0; i<n; ++i) {
            int &u = ch[x][i];
            if (!u) {
                u = ch[f[x]][i];
                continue;
            }
            q[tail++] = u; f[u] = ch[f[x]][i];
        }
    }
    a[t][t] = 1;
    for (int i=0; i<t; ++i) {
        a[i][i] = n; a[i][t+1] = n;
        for (int j=0; j<n; ++j) a[i][ch[i][j]] -= 1;
    }
    for (int i=0, c=0; i<=t; ++i, ++c) {
        for (int j=i; j<=t; ++j) if (a[j][c]) {
            if (j > i) for (int k=t+1; k>=c; --k) {
                long long x = a[i][k]; a[i][k] = a[j][k]; a[j][k] = x;
            }
            break;
        }
        if (a[i][c] == 0) continue;
        for (int j=0; j<=t; ++j) if (j!=i && a[j][c])
            for (int k=t+1; k>=c; --k) a[j][k] = a[i][c]*a[j][k] - a[j][c]*a[i][k];
    }
    return a[0][t+1] / a[0][0];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) {
        if (kase > 1) cout << endl;
        cout << "Case " << kase << ":" << endl << solve() << endl;
    }
    return 0;
}