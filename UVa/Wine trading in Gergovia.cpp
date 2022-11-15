/**
 * UVa11054
 * Gergovia的酒交易
 * University of Ulm Local Contest 2006
 */

#include <iostream>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int n;
    while (cin>>n && n) {
        long long ans = 0, v; cin >> v;
        for (int i=1; i<n; ++i) {
            int p; cin >> p;
            ans += abs(v);
            v += p;
        }
        cout << ans << endl;
    }
    return 0;
}