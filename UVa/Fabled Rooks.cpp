/**
 * UVa11134
 * 传说中的车
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 5010
short x[N], y[N];

struct interval {
    short i, a, b;
    interval(){};
    interval(short a, short b):a(a),b(b){}
    bool operator< (const interval &rhs) const {
        return b < rhs.b || (b==rhs.b && b<rhs.b);
    }
}xm[N], ym[N];

int main()
{
    short n;
    while (cin >> n && n) {
        for (short i=1; i<=n; ++i) cin >> xm[i].a >> ym[i].a >> xm[i].b >> ym[i].b, xm[i].i = i, ym[i].i = i;
        sort(xm+1, xm+n+1);
        bool noAns = false, used[N] = {false};
        for (short i=1, j; i<=n && !noAns; ++i) {
            for (j=1; j<=n; ++j) if (!used[j] && xm[j].a<=i && xm[j].b>=i) {
                used[j] = true; x[xm[j].i] = i; break;
            }
            if (j > n) noAns = true;
        }
        if (!noAns) {
            sort(ym+1, ym+n+1);
            bool used1[N] = {false};
            for (short i=1, j; i<=n && !noAns; ++i) {
                for (j=1; j<=n; ++j) if (!used1[j] && ym[j].a<=i && ym[j].b>=i) {
                    used1[j] = true; y[ym[j].i] = i; break;
                }
                if (j > n) noAns = true;
            }
        }
        if (noAns) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            for (short i=1; i<=n; ++i) cout << x[i] << ' ' << y[i] << endl;
        }
    }
    return 0;
}