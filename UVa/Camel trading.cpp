/**
 * UVa10700
 */

#include <iostream>
using namespace std;

#define N 15
char op[N]; int a[N]; long long d[N][N], e[N][N];

long long get(long long x, long long y, char op) {
    return op=='+' ? x+y : x*y;
}

void solve() {
    int n = 0;
    while (cin >> a[n++]) {
        op[n-1] = cin.get();
        if (op[n-1] == '\n') break;
    }
    for (int i=0; i<n; ++i) d[i][i] = e[i][i] = a[i];
    for (int l=1; l<n; ++l) for (int i=n-l-1; i>=0; --i) {
        int j = i+l;
        d[i][j] = get(d[i][i], d[i+1][j], op[i]);
        e[i][j] = get(e[i][i], e[i+1][j], op[i]);
        for (int k=i+1; k<j; ++k) {
            d[i][j] = max(d[i][j], get(d[i][k], d[k+1][j], op[k]));
            e[i][j] = min(e[i][j], get(e[i][k], e[k+1][j], op[k]));
        }
    }
    cout << "The maximum and minimum are " << d[0][n-1] << " and " << e[0][n-1] << '.' << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}