/**
 * UVa1617
 * 笔记本
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 100010
struct seg {
    int r, d;
    bool operator< (const seg& rhs) const {
        return d < rhs.d || (d==rhs.d && r < rhs.r);
    }
} a[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        for (int i=0; i<n; ++i) cin >> a[i].r >> a[i].d;
        sort(a, a+n);
        int d = a[0].d, s = 0;
        for (int i=1; i<n; ++i)
            if (a[i].r > d) ++s, d=a[i].d;
            else if (a[i].d > d) ++d;
        cout << s << endl;
    }
    return 0;
}