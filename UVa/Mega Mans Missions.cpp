/**
 * UVa11795
 * 洛克人的难题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 18
long long d[1<<N]; int c[1<<N];

long long solve() {
    memset(d, 0, sizeof(d)); d[1] = 1; c[0] = 0;
    int n; cin >> n; ++n;
    for (int i=0; i<n; ++i) c[1<<i] = 0;
    for (int i=0; i<n; ++i) for (int j=1; j<n; ++j){
        char f; cin >> f;
        if (f == '1') c[1<<i] |= 1<<j;
    }
    int m = (1<<n)-1;
    for (int s=1; s<=m; ++s) {
        c[s] = c[s&(-s)] | c[s&(s-1)];
        for (int i=1; i<n; ++i) if (~s&1<<i && c[s]&1<<i) d[s | 1<<i] += d[s];
    }
    return d[m];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) cout << "Case " << kase << ": " << solve() << endl;
    return 0;
}