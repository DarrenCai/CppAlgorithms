/**
 * UVa11039
 * 设计建筑物
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 500500
int c[N], n;

bool cmp(int a, int b) {
    return abs(a) < abs(b);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int p; cin >> p;
    while (p--) {
        cin >> n;
        for (int i=0; i<n; ++i) cin >> c[i];
        sort(c, c+n, cmp);
        int d0 = c[0]<0, d1 = c[0]>0;
        for (int i=1; i<n; ++i) {
            int dd0 = d0, dd1 = d1;
            c[i] < 0 ? dd0 = max(dd0, 1+d1) : dd1 = max(dd1, 1+d0);
            d0 = dd0; d1 = dd1;
        }
        cout << max(d0, d1) << endl;
    }
    return 0;
}