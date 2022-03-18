/**
 * LA4238
 */

#include <iostream>
#include <set>
using namespace std;

#define N 2050
struct point {
    short x, y, z;
    bool operator< (const point& rhs) const {
        return x<rhs.x || (x==rhs.x && y<rhs.y) || (x==rhs.x && y==rhs.y && z<rhs.z);
    }
} q[N];

short count(const point& p, const set<point>& s) {
    int cnt = 0; point pp;
    pp = p; pp.x = p.x-1; if (s.count(pp)) ++cnt;
    pp = p; pp.y = p.y-1; if (s.count(pp)) ++cnt;
    pp = p; pp.z = p.z-1; if (s.count(pp)) ++cnt;
    pp = p; pp.x = p.x+1; if (s.count(pp)) ++cnt;
    pp = p; pp.y = p.y+1; if (s.count(pp)) ++cnt;
    pp = p; pp.z = p.z+1; if (s.count(pp)) ++cnt;
    return cnt;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        short n; cin >> n; set<point> s;
        short x = n+1; char c;
        for (short i=1; i<=n; ++i) {
            cin >> q[i].x >> c >> q[i].y >> c >> q[i].z;
            if (s.count(q[i])) x = min(x, i);
            else s.insert(q[i]);
        }
        short head = n+1, tail = n+2, ans = 6; set<point> s1;
        q[head] = *s.begin(); s.erase(s.begin()); s1.insert(q[0]);
        while (head < tail) {
            const point& pp = q[head++];
            point p = pp; p.x = pp.x-1;
            if (s.count(p)) {
                ans += 6 - 2*count(p, s1); q[tail++] = p; s.erase(p); s1.insert(p);
            }
            p = pp; p.y = pp.y-1;
            if (s.count(p)) {
                ans += 6 - 2*count(p, s1); q[tail++] = p; s.erase(p); s1.insert(p);
            }
            p = pp; p.z = pp.z-1;
            if (s.count(p)) {
                ans += 6 - 2*count(p, s1); q[tail++] = p; s.erase(p); s1.insert(p);
            }
            p = pp; p.x = pp.x+1;
            if (s.count(p)) {
                ans += 6 - 2*count(p, s1); q[tail++] = p; s.erase(p); s1.insert(p);
            }
            p = pp; p.y = pp.y+1;
            if (s.count(p)) {
                ans += 6 - 2*count(p, s1); q[tail++] = p; s.erase(p); s1.insert(p);
            }
            p = pp; p.z = pp.z+1;
            if (s.count(p)) {
                ans += 6 - 2*count(p, s1); q[tail++] = p; s.erase(p); s1.insert(p);
            }
        }
        if (s.empty() && x>n) {
            cout << kase << ' ' << ans << endl;
        } else {
            s.clear(); s.insert(q[1]);
            for (short i=2; i<=n; ++i) {
                if (!count(q[i], s)) {
                    x = min(x, i);
                    break;
                }
                s.insert(q[i]);
            }
            cout << kase << " NO " << x << endl;
        }
    }
    return 0;
}
