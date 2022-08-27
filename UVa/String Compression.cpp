/**
 * UVa1351/LA3363
 * 字符串压缩
 * Seoul 2005
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 220
struct node {int  c, x, y;} d[N][N]; int x[N*N>>1][2], t; char s[N];

bool equal(int a, int b, int c) {
    for (int i=a, j=c; i<b; ++i, ++j) if (s[i]!=s[j]) return false;
    return true;
}

int find(int t0, int a, int b) {
    for (int i=t0; i<t; ++i) if (equal(a, b, x[i][0])) return i;
    x[t][0] = a; x[t][1] = b-a;
    return t++;
}

int solve() {
    cin >> s;
    int n = strlen(s); t = 0;
    for (int l=1; l<=n; ++l) {
        x[t][0] = 0; x[t][1] = l;
        for (int i=0, j=n-l, t0=t++; i<=j; ++i) {
            int k=i+l-1, y = find(t0, i, k+1); node& c = d[i][k]; c.c = 1; c.x = y; c.y = y;
            for (int m=i; m<k; ++m) {
                const node &a = d[i][m], &b = d[m+1][k];
                if (a.x == b.x) {
                    int cc = a.c + b.c, ll = (cc<10 ? 1 : (cc<100 ? 2 : 3)) + 2 + x[a.x][1];
                    c.c = cc; c.x = a.x;
                    if (ll < x[y][1]) x[y][1] = ll;
                } else {
                    int ll = x[a.y][1] + x[b.y][1];
                    if (ll < x[y][1]) x[y][1] = ll;
                }
            }
        }
    }
    return x[t-1][1];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << solve() << endl;
    return 0;
}