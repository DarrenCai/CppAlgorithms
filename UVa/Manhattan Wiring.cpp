/**
 * UVa1214/LA3620
 * 连线
 * Japan 2006
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 9
int p[] = {1,3,9,27,81,243,729,2187,6561,19683,59049}, d[9][59049], q[4782969], m, n, h, t; bool inq[59049], no;

void upd(int k, int s, int v) {
    if (!inq[s]) d[k][s] = v, q[t++] = s, inq[s] = true;
    else if (d[k][s] > v) d[k][s] = v;
}

void solve() {
    d[0][0] = q[0] = h = no = 0; t = 1;
    for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) {
        int a, k = j+1<m ? j+1 : 0, t0 = t; cin >> a;
        if (no) continue;
        memset(inq, 0, sizeof(inq));
        while (h < t0) {
            int s = q[h++], f = s/p[j]%3, b = s/p[m];
            if (a == 2 || a == 3) {
                int y = a-1;
                if ((f && f!=y) || (b && b!=y) || (f && b)) continue;
                if (f == 0 && b == 0) {
                    if (j+1 < m) upd(k, s+y*p[m], d[j][s]+1);
                    if (i+1 < n) upd(k, s+y*p[j], d[j][s]+1);
                } else if (f == y) upd(k, s-f*p[j], d[j][s]+1);
                else upd(k, s-b*p[m], d[j][s]+1);
            } else if (a == 0) {
                if (f && b) {
                    if (f == b) upd(k, s-b*p[m]-f*p[j], d[j][s]+2);
                } else if (f) {
                    if (j+1 < m) upd(k, s+f*(p[m]-p[j]), d[j][s]+2);
                    if (i+1 < n) upd(k, s, d[j][s]+2);
                } else if (b) {
                    if (j+1 < m) upd(k, s, d[j][s]+2);
                    if (i+1 < n) upd(k, s-b*(p[m]-p[j]), d[j][s]+2);
                } else {
                    upd(k, s, d[j][s]);
                    if (i+1 < n && j+1 < m) upd(k, s+p[m]+p[j], d[j][s]+2), upd(k, s+2*p[m]+2*p[j], d[j][s]+2);
                }
            } else if (f == 0 && b == 0) upd(k, s, d[j][s]);
        }
        if (h == t) no = true;
    }
    cout << (no ? 0 : d[0][0])/2 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m && n) solve();
    return 0;
}