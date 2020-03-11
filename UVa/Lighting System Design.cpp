/**
 * UVa11400
 * 照明系统设计
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define INF 3000000
#define N 1010

struct bulb {
    int v, k, c, l;
    bool operator< (const bulb& rhs) const {
        return v < rhs.v;
    }
} a[N];
int s[N]={0}, d[N]={0};

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int n;
    while (cin >> n && n) {
        for (int i=1; i<=n; ++i) cin >> a[i].v >> a[i].k >> a[i].c >> a[i].l;
        sort(a+1, a+1+n);
        for (int i=1; i<=n; ++i) {
            s[i] = a[i].l + s[i-1]; d[i] = INF;
            for (int j=0; j<i; ++j) d[i] = min(d[i], d[j] + (s[i]-s[j])*a[i].c + a[i].k);
        }
        cout << d[n] << endl;
    }
    return 0;
}