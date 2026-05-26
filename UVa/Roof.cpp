/**
 * UVa1138/LA2947
 * 十一月的雨
 * CERC 2003
 */

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define M 80200
#define N 102
int tt[M], c[M], d[M], x[M], x1[M], x2[M], y[M], y2[M], m, n, t;

struct seg {
    int i; double l, r;
    bool operator< (const seg& rhs) const {
        return l < rhs.l;
    }
} s[M][N];

struct cmp {
    bool operator() (int i, int j) const {
        double x = min(s[i][c[i]].l, s[i][c[i]].r), y = min(s[j][c[j]].l, s[j][c[j]].r);
        return x > y || (x == y && i < j);
    }
};

double interp(int i, double x) {
    return ((x2[i]-x)*y[i] + (x-x1[i])*y2[i]) / (x2[i]-x1[i]);
}

bool cmpl(const seg& e, double y) {
    return e.l < y;
}

bool cmpr(const seg& e, double y) {
    return e.r < y;
}

void solve() {
    cin >> n;
    for (int i=0; i<n; ++i) cin >> x1[i] >> y[i] >> x2[i] >> y2[i], d[i] = 0, x[i] = x1[i], x[i+n] = x2[i];
    m = n<<1; sort(x, x+m); m = unique(x, x+m) - x - 1;
    for (int i=0; i<m; ++i) tt[i] = 0;
    for (int i=0; i<n; ++i) for (int j = lower_bound(x, x+m, x1[i]) - x; x[j] < x2[i]; ++j)
        s[j][tt[j]++] = {i, interp(i, x[j]), interp(i, x[j+1])};
    set<int, cmp> ss;
    for (int i=0; i<m; ++i) {
        sort(s[i], s[i] + tt[i]);
        if (tt[i] > 0) c[i] = tt[i] - 1, ss.insert(i);
    }
    while (!ss.empty()) {
        int i = *ss.begin(); const seg& e = s[i][c[i]];
        if (c[i]+1 == tt[i]) d[e.i] += x[i+1] - x[i];
        if (e.l < e.r && x[i] == x1[e.i]) {
            int x = -1; double y = -10.;
            if (c[i] > 0) x = s[i][c[i]-1].i, y = s[i][c[i]-1].l;
            if (i > 0) {
                int j = lower_bound(s[i-1], s[i-1] + tt[i-1], e.l, cmpr) - s[i-1] - 1;
                if (j >= 0 && s[i-1][j].r > y) x = s[i-1][j].i;
            }
            if (x >= 0) d[x] += d[e.i];
        } else if (e.l > e.r && x[i+1] == x2[e.i]) {
            int x = -1; double y = -10.;
            if (c[i] > 0) x = s[i][c[i]-1].i, y = s[i][c[i]-1].r;
            if (i+1 < m) {
                int j = lower_bound(s[i+1], s[i+1] + tt[i+1], e.r, cmpl) - s[i+1] - 1;
                if (j >= 0 && s[i+1][j].l > y) x = s[i+1][j].i;
            }
            if (x >= 0) d[x] += d[e.i];
        }
        ss.erase(ss.begin());
        if (c[i]--) ss.insert(i);
    }
    for (int i=0; i<n; ++i) cout << d[i] << endl;
    if (t) cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t;
    while (t--) solve();
    return 0;
}