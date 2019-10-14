/**
 * UVa1615
 * 高速公路
 */

#include <iostream>
#include <cmath>
#include <set>
using namespace std;

#define max(a, b) (a>b ? a:b)
#define min(a, b) (a<b ? a:b)
#define N 100010
struct interval {
    double min, max;
    bool operator< (const interval& p) const {
        if (max < p.min) return true;
        if (min > p.max) return false;
        return min < p.min || (min==p.min && max<p.max);
    }
    bool intersects(const interval& p) const {
        return max >= p.min && min <= p.max;
    }
};
double l, d; int n; interval p; set<interval> s;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> l >> d >> n) {
        s.clear();
        for (int i=0; i<n; ++i) {
            double x, y; cin >> x >> y;
            y = sqrt(d*d - y*y);
            p.min = max(0, x-y);
            p.max = min(l, x+y);
            if (i) {
                set<interval>::iterator it = s.lower_bound(p);
                if (it == s.end()) --it;
                if (it->intersects(p)) {
                    p.min = max(p.min, it->min);
                    p.max = min(p.max, it->max);
                    s.erase(it);
                }
            }
            s.insert(p);
        }
        cout << s.size() << endl;
    }
    return 0;
}