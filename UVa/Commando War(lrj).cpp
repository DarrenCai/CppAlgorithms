/**
 * UVa11729
 * 突击战
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 1020
int b[N], j[N], p[N], n;

bool cmp(int x, int y) {
    return j[x] > j[y];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int kase = 0;
    while (cin>>n && n) {
        for (int i=0; i<n; ++i) cin >> b[i] >> j[i], p[i] = i;
        sort(p, p+n, cmp);
        int s = 0, t = 0;
        for (int i=0; i<n; ++i) {
            t = max(t, b[p[i]]+j[p[i]]) - b[p[i]];
            s += b[p[i]];
        }
        cout << "Case " << ++kase << ": " << s+t << endl;
    }
    return 0;
}