/**
 * UVa11529
 * 奇怪的税
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 1205
int n, kase = 0;
struct VRA {
    int x, y;
    int quad() const {
        return x>0 && y>=0 ? 1 : (x<=0 && y>0 ? 2 : (x<0 && y<=0 ? 3 : 4));
    }
    int cross(const VRA& rhs) const {
        return x*rhs.y - rhs.x*y;
    }
    // int dot(const VRA& rhs) const {
    //     return x*rhs.x + y*rhs.y;
    // }
    bool operator< (const VRA& rhs) const {
        int q = quad() - rhs.quad();
        if (q == 0) return cross(rhs) > 0;
        return q < 0;
    }
} p[N], a[N<<1];

int outside(int k) {
    int ans = 0, m = n-1;
    for (int i=0, j=0; i<n; ++i) if (i != k) a[j].x = p[i].x - p[k].x, a[j++].y = p[i].y - p[k].y;
    sort(a, a+m);
    for (int i=0; i<m; ++i) a[m+i] = a[i];
    for (int i=0, j=0; i<m; ++i) {
        if (j == i) ++j;
        while (j<m+i && a[i].cross(a[j])>0) ++j;
        ans += (j-i-1)*(j-i-2)/2;
    }
    return ans;
}

void solve() {
    for (int i=0; i<n; ++i) cin >> p[i].x >> p[i].y;
    long long b = n*(n-1ll)*(n-2)/6, c = b*(n-3);
    for (int i=0; i<n; ++i) c -= outside(i);
    cout << "City " << ++kase << ": " << c/b << '.';
    c = c%b * 100;
    c = c/b + (c%b*2 >= b);
    if (c < 10) cout << 0;
    cout << c << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n && n) solve();
    return 0;
}