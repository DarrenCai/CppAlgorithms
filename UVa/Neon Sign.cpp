/**
 * UVa1510/LA5846
 * 霓虹灯广告牌
 * Daejon 2011
 */

#include <iostream>
using namespace std;

#define N 1010
int c[N];

void solve() {
    int n; cin >> n;
    for (int i=0; i<n; ++i) c[i] = 0;
    for (int i=1; i<n; ++i) for (int j=i; j<n; ++j) {
        int color; cin >> color;
        if (color) ++c[i-1], ++c[j];
    }
    int x = 0;
    for (int i=0; i<n; ++i) x += c[i]*(n-1-c[i]);
    cout << n*(n-1)*(n-2)/6 - x/2 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}