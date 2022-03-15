/**
 * UVa1445
 * 积木艺术
 */

#include <iostream>
using namespace std;

#define N 25
short c1[N], c2[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short w, d, v;
    while (cin>>w>>d && w) {
        for (short i=0; i<N; ++i) c1[i] = c2[i] = 0;
        for (short i=0; i<w; ++i) cin >> v, ++c1[v];
        for (short i=0; i<d; ++i) cin >> v, ++c2[v];
        v = 0;
        for (short i=1; i<N; ++i) v += i*max(c1[i], c2[i]);
        cout << v << endl;
    }
    return 0;
}
