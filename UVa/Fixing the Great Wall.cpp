/**
 * UVa1336
 * 修缮长城
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 1010
struct node {
    unsigned int x; unsigned short d;
} s1[N], s2[N];
bool le (const node& a, const node& b) {
    return a.x < b.x;
}
bool gr (const node& a, const node& b) {
    return a.x > b.x;
}
unsigned long long d[N][N][2], d1[N], d2[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    unsigned int n, v, x;
    while (cin >> n >> v >> x && n) {
        short n1=0, n2=0; unsigned long long ct=0;
        s1[n1].x = x; s1[n1++].d = 0; s2[n2].x = x; s2[n2++].d = 0;
        for (short i=0; i<n; ++i) {
            unsigned short c, d; cin >> x >> c >> d; ct += c;
            if (x < s1[0].x) {
                s1[n1].x = x; s1[n1++].d = d;
            } else {
                s2[n2].x = x; s2[n2++].d = d;
            }
        }
        sort(s1, s1+n1, gr); sort(s2, s2+n2, le);
        d1[n1-1] = s1[n1-1].d; d2[n2-1] = s2[n2-1].d;
        for (short i=n1-2; i>=0; --i) d1[i] = d1[i+1] + s1[i].d;
        for (short i=n2-2; i>=0; --i) d2[i] = d2[i+1] + s2[i].d;
        d[n1][n2][0] = d[n1][n2][1] = 0;
        for (short i=n2-1; i>=0; --i) {
            d[n1][i][0] = d[n1][i+1][1] + d2[i]*(s2[i].x - s1[n1-1].x);
            d[n1][i][1] = d[n1][i+1][1] + (i==0 ? 0ull : d2[i]*(s2[i].x - s2[i-1].x));
        }
        for (short i=n1-1; i>=0; --i) {
            d[i][n2][0] = d[i+1][n2][0] + (i==0 ? 0ull : d1[i]*(s1[i-1].x - s1[i].x));
            d[i][n2][1] = d[i+1][n2][0] + d1[i]*(s2[n2-1].x - s1[i].x);
            for (short j=n2-1; j>=0; --j) {
                d[i][j][0] = d[i+1][j][0] + (i==0 ? 0ull : (d1[i] + d2[j])*(s1[i-1].x - s1[i].x));
                unsigned long long t = d[i][j+1][1] + (d1[i] + d2[j])*(s2[j].x - (i==0 ? s2[0].x : s1[i-1].x));
                if (t < d[i][j][0]) d[i][j][0] = t;
                d[i][j][1] = d[i][j+1][1] + (j==0 ? 0ull : (d1[i] + d2[j])*(s2[j].x - s2[j-1].x));
                t = d[i+1][j][0] + (d1[i] + d2[j])*((j==0 ? s1[0].x : s2[j-1].x) - s1[i].x);
                if (t < d[i][j][1]) d[i][j][1] = t;
            }
        }
        cout << d[0][0][0]/v + ct << endl;
    }
    return 0;
}