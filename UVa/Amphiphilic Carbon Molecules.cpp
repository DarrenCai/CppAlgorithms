/**
 * UVa1606
 * 两亲性分子
 */

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define N 1010
struct Molecule {
    short x, y;
    union {
        double rad;
        short r;
    };
    bool operator< (const Molecule &rhs) const {
        return rad < rhs.rad;
    }
}origin[N], sorted[N];

int main()
{
    short n;
    while (cin >> n && n) {
        for (short i=0; i<n; ++i) cin >> origin[i].x >> origin[i].y >> origin[i].r;
        if (n <= 3) cout << n << endl;
        else {
            short ans = 0;
            for (short i=0; i<n; ++i) {
                short k = 0, cnt = 2;
                for (short j=0; j<n; ++j) if (j != i) {
                    sorted[k].x = origin[j].x - origin[i].x;
                    sorted[k].y = origin[j].y - origin[i].y;
                    if (origin[j].r) sorted[k].x = -sorted[k].x, sorted[k].y = -sorted[k].y;
                    sorted[k].rad = atan2(sorted[k].y, sorted[k].x);
                    ++ k;
                }
                sort(sorted, sorted + k);
                for (short l=0, r=0; l<k; ++l) {
                    if (r == l) r = (r+1)%k, ++cnt;
                    while (r != l && sorted[l].x * sorted[r].y - sorted[r].x * sorted[l].y >= 0) r = (r+1)%k, ++cnt;
                    ans = max(ans, --cnt);
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}