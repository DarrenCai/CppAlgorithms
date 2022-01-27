/**
 * UVa10881
 * 蚂蚁
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 10200
int p[N], L, T, n;
struct node {
    int p, x, d;
    bool operator< (const node& rhs) const {
        return x < rhs.x;
    }
} a[N], b[N]; 

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) {
        cout << "Case #" << kase << ':' << endl;
        cin >> L >> T >> n;
        for (int i=0; i<n; ++i) {
            a[i].p = i;
            char c; cin >> a[i].x >> c;
            b[i].d = a[i].d = c=='R';
            b[i].x = a[i].d ? a[i].x + T : a[i].x - T;
        }
        sort(a, a+n);
        for (int i=0; i<n; ++i) p[a[i].p] = i;
        sort(b, b+n);
        for (int i=1; i<n; ++i) if (b[i].x == b[i-1].x) b[i].d = b[i-1].d = 2;
        for (int i=0; i<n; ++i) {
            node& t = b[p[i]];
            if (t.x<0 || t.x>L) cout << "Fell off" << endl;
            else cout << t.x << (t.d==2 ? " Turning" : (t.d ? " R" : " L")) << endl;
        }
        cout << endl;
    }
    return 0;
}