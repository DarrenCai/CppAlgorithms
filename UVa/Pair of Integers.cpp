/**
 * UVa1654
 * 整数对
 */

#include <iostream>
#include <set>
using namespace std;

struct node {
    int x, y;
    node(int x, int y):x(x),y(y){}
    bool operator< (const node& rhs) const {
        return x < rhs.x;
    }
};
int p[10]; set<node> ans;

void solve(int a, short x, int n) {
    if (n == 0) {
        ans.insert(node(a*p[x], a*p[x-1]));
        return;
    }
    short y = x;
    while (p[y] > n) --y;
    short b = n/p[y];
    if (b==1) {
        if (y>1) {
            int z = n-99*p[y-2];
            if (z >= 0) solve(a*p[x-y+1] + 9, y-1, z);
        }
        if (y>=1) {
            int z = n-9*p[y-1];
            if (~z&1) {
                z >>= 1;
                if (z < p[y-1]) ans.insert(node(a*p[x] + 9*p[y-1] + z, a*p[x-1] + z));
            }
        }
    }
    if (y == x) return;
    if (y == 0) {
        if (x) ans.insert(node(a*p[x] + b, a*p[x-1]));
        if (~b&1 && x-1 > y) {
            b >>= 1;
            ans.insert(node(a*p[x] + b, a*p[x-1] + b));
        }
        return;
    }
    if (y+1 < x && ~n&1) ans.insert(node(a*p[x]+(n>>1), a*p[x-1]+(n>>1)));
    int z = n-11*b*p[y-1];
    if (z>=0) solve(a*p[x-y] + b, y, z);
    z = n-b*p[y];
    if (~z&1) ans.insert(node(a*p[x] + b*p[y] + (z>>1), a*p[x-1] + (z>>1)));
    solve(a*p[x-y] + b-1, y, n-11*(b-1)*p[y-1]);
    z = n-(b-1)*p[y];
    if (~z&1) ans.insert(node(a*p[x] + (b-1)*p[y] + (z>>1), a*p[x-1] + (z>>1)));
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    p[0] = 1; for (short i=1; i<10; ++i) p[i] = 10*p[i-1];
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n > 10) {
            ans.clear();
            int x = 9;
            while (p[x] > n) --x;
            short a = n/p[x];
            if (~n&1) {
                if (a > 1) {
                    int y = (n-(a-1)*p[x]) >> 1;
                    ans.insert(node((a-1)*p[x]+y, y));
                }
                int y = (n-a*p[x]) >> 1;
                ans.insert(node(a*p[x]+y, y));
            }
            int y = n-11*a*p[x-1];
            if (y >= 0) solve(a, x, y);
            if (a > 1) {
                solve(a-1, x, n-11*(a-1)*p[x-1]);
            } else {
                if (--x >= 1) {
                    y = n-99*p[x-1];
                    if (y >= 0) solve(9, x, y);
                }
                if (x > 0) {
                    y = n-9*p[x];
                    if (~y&1) {
                        y >>= 1;
                        if (y < p[x]) ans.insert(node(9*p[x] + y, y));
                    }
                }
            }
            cout << ans.size() << endl;
            for (set<node>::iterator it = ans.begin(); it != ans.end(); ++it) {
                cout << it->x << " + ";
                int x = 9; while (p[x] > it->x) --x;
                if (p[x] <= it->x) ++x;
                int y = 9; while (p[y] > it->y) --y;
                if (p[y] <= it->y) ++y;
                y = max(y, 1);
                while (++y < x) cout << 0;
                cout << it->y << " = " << n << endl;
            }
        } else cout << 1 << endl << n << " + 0 = " << n << endl;
        if (t) cout << endl;
    }
    return 0;
}