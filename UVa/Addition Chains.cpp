/**
 * UVa529
 * Ulm Local 1997
 */

#include <iostream>
using namespace std;

short a[20], n, m;

short h(short v) {
    short c = 0;
    while (v<n) v<<=1, ++c;
    return c;
}

bool IDAStar(short curr = 1) {
    if (curr==m) return a[curr-1] == n;
    for (short i=curr-1; i>=0; --i) {
        a[curr] = a[curr-1]+a[i];
        if (a[curr] > n) continue;
        if (curr + h(a[curr]) >= m) break;
        if (IDAStar(curr+1)) return true;
    }
    return false;
}

void solve() {
    if (n==1) {
        cout << 1 << endl;
    } else {
        for (m=2; !IDAStar(); ++m);
        cout << a[0];
        for (short i=1; i<m; ++i) cout << ' ' << a[i];
        cout << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    a[0] = 1;
    while (cin>>n && n) solve();
    return 0;
}