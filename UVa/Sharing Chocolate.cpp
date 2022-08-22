/**
 * UVa1099/LA4794
 * 分享巧克⼒
 * World Finals 2010
 */

#include <iostream>
#include <cstring>
using namespace std;

#define C 110
#define N 16
short c[1<<N], f[1<<N][C], d[1<<N][N][2], n, x, y;;

bool expand(short s, int ss) {
    for (short a=1, b; a*a<=s && a<=x; ++a) if (s%a==0 && (b=s/a)<=y) {
        d[ss][c[ss]][0] = a; d[ss][c[ss]++][1] = b; f[ss][a] = b; f[ss][b] = a;
    }
    return c[ss] > 0;
}

void expand(int s, short x1, short y1) {
    if (f[s][x1]) return;
    if (x1 > y1) {
        short t = x1; x1 = y1; y1 = t;
    }
    if (x1>x || y1>y) return;
    d[s][c[s]][0] = x1; d[s][c[s]++][1] = y1; f[s][x1] = y1; f[s][y1] = x1;
}

bool check() {
    cin >> x >> y;
    if (x > y) {
        short t = x; x = y; y = t;
    }
    memset(c, 0, sizeof(c)); memset(f, 0, sizeof(f));
    int s = 0, ss = x*y, a, v; bool ok = true;
    for (short i=0; i<n; ++i) {
        cin >> a;
        if ((s += a) > ss || !expand(a, 1<<i)) ok = false;
    }
    if (!ok || s < ss) return false;
    if (n == 1) return true;
    a = (1<<n)-1;
    for (s=1; s<a; ++s) for (ss=s&(s-1), v=s>>1; ss>v; ss=s&(ss-1)) {
        short cc = min(c[ss], c[s^ss]); int b = c[ss]==cc ? ss : s^ss;
        const short (&r)[N][2] = d[b], (&ff)[C] = f[s^b];
        for (short i=0; i<cc; ++i) {
            if (ff[r[i][0]]) expand(s, r[i][0], r[i][1] + ff[r[i][0]]);
            if (ff[r[i][1]]) expand(s, r[i][1], r[i][0] + ff[r[i][1]]);
        }
    }
    for (s=a&(a-1), v=a>>1; s>v; s=a&(s-1)) {
        short (&f1)[C] = f[s], (&f2)[C] = f[a^s];
        if ((f1[x] && f2[x]) || (f1[y] && f2[y])) return true;
    }
    return false;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int kase = 0;
    while (cin>>n && n) cout << "Case " << ++kase << ": " << (check() ? "Yes" : "No") << endl;
    return 0;
}