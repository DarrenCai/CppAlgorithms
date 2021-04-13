/**
 * UVa1646
 * 圈图的匹配
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 10010
#define M 1000000000
int v[N][340]; short l[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    l[3] = l[4] = 1; v[3][0] = 4; v[4][0] = 7;
    for (short i=5; i<N; ++i) {
        int (&a)[340] = v[i], (&b)[340] = v[i-1], (&c)[340] = v[i-2];
        short tb = l[i-1], tc = l[i-2], &t = l[i] = tb;
        int r = 0;
        for (short j=0; j<tc; ++j) {
            long long v = (long long)b[j] + c[j] + r;
            a[j] = v%M;
            r = v/M;
        }
        if (tb > tc) {
            long long v = (long long)b[t-1] + r;
            a[t-1] = v%M;
            r = v/M;
        }
        if (r) a[t++] = r;
    }
    cout << setfill('0');
    short n;
    while (cin>>n) {
        short t = l[n]-1; cout << v[n][t];
        while (t--) cout << setw(9) << v[n][t];
        cout << endl;
    }
    return 0;
}