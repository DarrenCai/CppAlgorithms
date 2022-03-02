/**
 * UVa11100
 * 旅⾏2007
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 10050
int a[N], kase = 0; short n, k;

void solve() {
    for (short i=0; i<n; ++i) cin >> a[i];
    sort(a, a+n);
    short c = k = 1;
    for (short i=1; i<n; ++i) a[i] == a[i-1] ? k = max(k, ++c) : c = 1;
    if (kase++) cout << endl;
    cout << k << endl;
    for (short i=0; i<k; ++i) {
        cout << a[i];
        for (short j=i+k; j<n; j+=k) cout << ' ' << a[j];
        cout << endl;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n && n) solve();
    return 0;
}