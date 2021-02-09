/**
 * UVa12222
 * 山路
 */

#include <iostream>
#include <cstring>
// #include <algorithm>
using namespace std;

#define N 220
struct node {
    int t, d;
    // bool operator< (const node& rhs) const {
    //     return t < rhs.t;
    // }
} a[N], b[N];
int la, lb, d[N][N][2];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short c; cin >> c;
    while (c--) {
        short n; cin >> n; la = lb = 0;
        while (n--) {
            char ch; cin >> ch;
            ch == 'A' ? cin >> a[++la].t >> a[la].d : cin >> b[++lb].t >> b[lb].d;
        }
        // sort(a+1, a+la+1); sort(b+1, b+lb+1);
        memset(d, 0x33, sizeof(d));
        d[0][0][0] = d[0][0][1] = 0;
        for (short i=0; i<=la; ++i) for (short j=0; j<=lb; ++j) {
            if (i>0) d[i][j][0] = min(d[i][j][0], max(d[i-1][j][1], a[i].t) + a[i].d);
            if (j>0) d[i][j][1] = min(d[i][j][1], max(d[i][j-1][0], b[j].t) + b[j].d);
            int s = d[i][j][1], e = 0;
            for (short k=i+1; k<=la; ++k) {
                s = max(s, a[k].t); e = max(s + a[k].d, e);
                d[k][j][0] = min(d[k][j][0], e);
                s += 10; e += 10;
            }
            s = d[i][j][0]; e = 0;
            for (short k=j+1; k<=lb; ++k) {
                s = max(s, b[k].t); e = max(s + b[k].d, e);
                d[i][k][1] = min(d[i][k][1], e);
                s += 10; e += 10;
            }
        }
        cout << min(d[la][lb][0], d[la][lb][1]) << endl;
    }
    return 0;
}