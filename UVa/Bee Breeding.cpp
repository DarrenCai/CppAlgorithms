/**
 * UVa808
 * 勤劳的蜜蜂
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 10268
#define C 58
short d[N][6], t[N] = {0}, q[2][12*C]; bool visit[N];
short calc(short a, short b) {
    if (a == b) return 0;
    memset(visit, 0, sizeof(visit));
    q[0][0] = a; visit[a] = true; short l[] = {1, 0};
    for (short c=1, cc=C<<1; c<cc; ++c) {
        short (&qp)[12*C] = q[(c&1)^1], (&qc)[12*C] = q[c&1], &lc = l[c&1] = 0;
        for (short i=l[(c&1)^1]-1; i>=0; --i) for (short j=t[qp[i]]-1; j>=0; --j) if (!visit[d[qp[i]][j]]) {
            if (d[qp[i]][j] == b) return c;
            visit[qc[lc++] = d[qp[i]][j]] = true;
        }
    }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short c=1, pa=1, pb=1, a, b; c<=C; ++c, pa=a, pb=b) {
        a = pb+1; b = pb+6*c;
        for (short i=a, v=pb; i<=b; ++i) {
            d[i][t[i]++] = v; d[v][t[v]++] = i;
            if ((i-a+1)%c) {
                v = v==pb ? pa:v+1;
                d[i][t[i]++] = v; d[v][t[v]++] = i;
            }
            short pre = i==a ? b:i-1;
            d[i][t[i]++] = pre; d[pre][t[pre]++] = i;
        }
    }
    short a, b;
    while (cin >> a >> b && a)
        cout << "The distance between cells " << a << " and " << b << " is " << calc(a, b) << '.' << endl;
    return 0;
}