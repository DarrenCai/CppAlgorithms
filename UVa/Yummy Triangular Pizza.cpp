/**
 * UVa12326/LA5704
 * 美味的三⾓匹萨
 * Shanghai 2011
 * http://oeis.org/A006534
 * 打表才能通过
 */

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define N 16

struct tri {
    short x, y; bool up;
    tri():up(false){}
    tri(short x, short y):x(x), y(y), up(false){}
    bool operator== (const tri& rhs) const {
        return x==rhs.x && y==rhs.y && up==rhs.up;
    }
    bool operator< (const tri& rhs) const {
        return x<rhs.x || (x==rhs.x && y<rhs.y) || (x==rhs.x && y==rhs.y && !up && rhs.up);
    }
    tri operator- (const tri& rhs) const {
        tri t; t.x = x - rhs.x; t.y = y - rhs.y; t.up = up;
        return t;
    }
    void operator-= (const tri& rhs) {
        x = x - rhs.x; y = y - rhs.y;
    }
    tri operator+ (const tri& rhs) const {
        tri t; t.x = x + rhs.x; t.y = y + rhs.y; t.up = up;
        return t;
    }
    void rotate() {
        short x1 = (x+y)>>1, y1 = (y-3*x)>>1;
        x = x1; y = y1; up = !up;
    }
} nx[] = {tri(-1, 1), tri(1, 1), tri(0, -2)};

struct pizza {
    tri s[N]; short n;
    pizza():n(0){}
    bool operator< (const pizza& rhs) const {
        for (short i=0; i<n; ++i) {
            if (s[i] < rhs.s[i]) return true;
            if (rhs.s[i] < s[i]) return false;
        }
        return false;
    }
    bool add(const tri& tri) {
        short i = lower_bound(s, s+n, tri) - s;
        if (i<n && s[i]==tri) return false;
        for (short j=n++; j>i; --j) s[j] = s[j-1];
        s[i] = tri;
        return true;
    }
    void rotate() {
        for (short i=0; i<n; ++i) s[i].rotate();
        sort(s, s+n);
        for (short i=n-1; i>=0; --i) s[i] -= s[0];
    }
};

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int ans[N] = {1, 1, 1, 4, 6, 19, 43, 120, 307, 866, 2336, 6588, 18373, 52119, 147700, 422016};
    // pizza p; p.add(tri()); set<pizza> s[N]; s[0].insert(p);
    // for (short i=1; i<N; ++i) {
    //     for (set<pizza>::iterator it = s[i-1].begin(); it != s[i-1].end(); ++it)
    //     for (short j=0; j<it->n; ++j) for (short k=0; k<3; ++k) {
    //         p = *it; tri t = p.s[j].up ? p.s[j] + nx[k] : p.s[j] - nx[k]; t.up = !p.s[j].up;
    //         if (p.add(t)) {
    //             bool f = true;
    //             for (short l=0; l<6; ++l) {
    //                 p.rotate();
    //                 if (s[i].count(p)) {
    //                     f = false; break;
    //                 }
    //             }
    //             if (f) s[i].insert(p);
    //         }
    //     }
    //     ans[i] = s[i].size();
    // }
    short T; cin >> T;
    for (short kase=1; kase<=T; ++kase) {
        short n; cin >> n;
        cout << "Case #" << kase << ": " << ans[n-1] << endl;
    }
    return 0;
}