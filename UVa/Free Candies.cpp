/**
 * UVa10118
 * 免费糖果
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 42
short h[4][N], n, t, c[4]; int d[N][N][N][N], cc;
struct Node { char p[4]; Node():p{0, 0, 0, 0}{} } q[N*N*N*N];
void decode(int c) {
    for (t=0; c>0; ++t, c>>=5) if (c&31) ::c[t] = c&31;
}
short encode(short c) {
    cc = 0; short add = 1;
    for (short i=0; i<t; ++i) ::c[i] == c ? add = -1 : cc = (cc<<5) + ::c[i];
    if (add == 1) cc = (cc<<5) + c;
    return t+add;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) {
        for (short i=0; i<n; ++i) cin >> h[0][i] >> h[1][i] >> h[2][i] >> h[3][i];
        int ans = 0, tail = 0; memset(d, -1, sizeof(d));
        d[0][0][0][0] = 0; q[tail++] = Node();
        for (int head = 0; head < tail; ++head) {
            const Node& v = q[head]; decode(d[v.p[0]][v.p[1]][v.p[2]][v.p[3]]);
            short c = v.p[0] + v.p[1] + v.p[2] + v.p[3] - t;
            for (short i=0; i<4; ++i) if (v.p[i] < n) {
                Node s = v; ++s.p[i]; int &ref = d[s.p[0]][s.p[1]][s.p[2]][s.p[3]];
                if (ref < 0) {
                    short tt = encode(h[i][s.p[i]-1]);
                    if (tt < t) ans = max(ans, c+2);
                    if (tt < 5) q[tail++] = s, ref = cc;
                }
            }
        }
        cout << (ans>>1) << endl;
    }
    return 0;
}