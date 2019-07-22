/**
 * UVa1471
 * 防线
 */

#include <iostream>
#include <set>
using namespace std;

#define N 200010
int a[N], f[N], g[N], ans, n;
struct elem {
    int h, c;
    elem(int h, int c):h(h),c(c){}
    bool operator< (const elem &rhs) const {
        return h < rhs.h;
    }
};
set<elem> s;

int main()
{
    short z; cin >> z;
    while (z --) {
        s.clear(); cin >> n; f[n-1] = 1; g[0] = 1;
        for (int i=0; i<n; ++i) cin >> a[i];
        for (int i=n-2; i>=0; --i) f[i] = a[i] < a[i+1] ? 1+f[i+1] : 1;
        for (int i=1; i<n; ++i) g[i] = a[i] > a[i-1] ? 1+g[i-1] : 1;
        ans = f[0]; s.insert(elem(a[0], g[0]));
        for (int i=1; i<n; ++i) {
            elem e(a[i], g[i]); bool keep = true;
            set<elem>::iterator it = s.lower_bound(e);
            if (it != s.begin()) {
                int t = f[i] + (--it)->c;
                if (t > ans) ans = t;
                if (e.c <= it->c) keep = false;
            }
            if (keep) {
                s.erase(e); it = ++ (s.insert(e).first);
                while (it != s.end() && it->c <= e.c) it = s.erase(it);
            }
        }
        cout << ans << endl;
    }
    return 0;
}