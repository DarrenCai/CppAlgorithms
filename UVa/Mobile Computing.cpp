/**
 * UVa1354/LA3403
 * 天平难题
 * Tokyo 2005
 */

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#define N 6
struct node {double l, r;}; int w[1<<N], m, n; double s; vector<node> g[1<<N]; bool f[1<<N];

void merge(int a, int b) {
    vector<node>& t = g[a | b];
    double u = w[b] / double(w[a] + w[b]), v = 1. - u;
    for (int i=g[a].size()-1; i>=0; --i) {
        double l = g[a][i].l, r = g[a][i].r;
        for (int j=g[b].size()-1; j>=0; --j) {
            double x = g[b][j].l, y = g[b][j].r;
            double c = max(u+l, x-v), d = max(v+y, r-u);
            if (c+d < s) t.push_back({c, d});
            if (x != y) {
                c = max(u+l, y-v); d = max(v+x, r-u);
                if (c+d < s) t.push_back({c, d});
            }
            if (l != r) {
                c = max(u+r, x-v); d = max(v+y, l-u);
                if (c+d < s) t.push_back({c, d});
                if (x != y) {
                    c = max(u+r, y-v); d = max(v+x, l-u);
                    if (c+d < s) t.push_back({c, d});
                }
            }
        }
    }
}

bool build(int x) {
    if (f[x]) return g[x].size() > 0;
    f[x] = true;
    if (x == (x&-x)) g[x].push_back({0., 0.});
    else for (int i=x&(x-1), j=x>>1; i>j; i=x&(i-1)) if (build(i) && build(x^i)) merge(i, x^i);
    return g[x].size() > 0;
}

void solve() {
    cin >> s >> n; m = (1<<n) - 1;
    for (int i=0; i<n; ++i) cin >> w[1<<i];
    if (n == 1) {
        cout << 0 << endl;
        return;
    }
    for (int i=1; i<=m; ++i) {
        if (i > (i&-i)) w[i] = w[i&-i] + w[i ^ i&-i];
        g[i].clear(); f[i] = false;
    }
    if (build(m)) {
        double x = 0.;
        for (int i=g[m].size()-1; i>=0; --i) x = max(x, g[m][i].l + g[m][i].r);
        cout << x << endl;
    } else cout << -1 << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(15);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}