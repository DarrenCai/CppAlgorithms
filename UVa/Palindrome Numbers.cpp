/**
 * UVa12050/LA2889
 * 回文数
 * Dhaka 2003
 */

#include <iostream>
#include <algorithm>
using namespace std;

long long a[11], p[11]; int n;

void solve(int n) {
    int x = lower_bound(a, a+10, n) - a - 1;
    n -= a[x];
    if (n <= 9*p[x+1]) {
        long long y = (n-1)/10 + p[x];
        if (y) cout << y;
        cout << (x==0 ? n : (n-1)%10);
        if (y) for (int i=0; i<x; ++i, y/=10) cout << y%10;
    } else {
        n -= 9*p[++x];
        long long y = n-1 + p[x];
        if (y) cout << y;
        if (y) for (int i=0; i<x; ++i, y/=10) cout << y%10;
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    a[0] = p[0] = 0; a[1] = 18; p[1] = 1;
    for (int i=2; i<11; ++i) a[i] = 10*(a[i-1]+2) - 2, p[i] = 10*p[i-1];
    while (cin>>n && n) solve(n);
    return 0;
}