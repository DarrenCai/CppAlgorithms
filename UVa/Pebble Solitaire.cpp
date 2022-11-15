/**
 * UVa10651
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 12
int d[1<<N], x[1<<N], a = 1<<N; char s[N+1];

bool cmp(int i, int j) {
    return d[i] < d[j];
}

void solve() {
    cin >> s;
    int x = 0;
    for (int i=0; i<N; ++i) if (s[i]=='o') x |= 1<<i;
    cout << d[x] << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    d[0] = 0; x[0] = 0;
    for (int s=1; s<a; ++s) d[x[s] = s] = 1 + d[s&(s-1)];
    sort(x, x+a, cmp);
    for (int i=1; i<a; ++i) {
        for (int j=N-3, &s=x[i]; j>=0; --j) if (s&(1<<j) && s&(1<<(j+1)) && ~s&(1<<(j+2)))
            d[s] = min(d[s], d[s^(1<<j)^(1<<(j+1))^(1<<(j+2))]);
        for (int j=N-1, &s=x[i]; j>1; --j) if (s&(1<<j) && s&(1<<(j-1)) && ~s&(1<<(j-2)))
            d[s] = min(d[s], d[s^(1<<j)^(1<<(j-1))^(1<<(j-2))]);
    }
    short t; cin >> t;
    while (t--) solve();
    return 0;
}