/**
 * UVa1665
 * 岛屿
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 1000100
int h[N], a[N], b[N], p[N], cnt[N], n, m;

bool cmp(int x, int y) {
    return h[x] < h[y];
}

bool cmp2(int v, int x) {
    return v < h[x];
}

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short z; cin >> z;
    while (z--) {
        cin >> n >> m;
        int cc = n*m, c = cc, mx = 0, tt = 0, t;
        for (int i=0; i<c; ++i) cin >> h[i], b[i] = i, mx = max(h[i], mx);
        cin >> t; for (int i=0; i<t; ++i) cin >> a[i];
        sort(b, b+c, cmp);
        for (int i=t-1; i>=0; --i) {
            if (mx > a[i]) {
                int j = upper_bound(b, b+c, a[i], cmp2) - b; tt += c-j;
                for (int k=j; k<c; ++k) p[b[k]] = b[k];
                for (int k=j; k<c; ++k) {
                    int q = b[k]-m, u = find(b[k]), v;
                    if (q>=0 && h[q]>a[i] && u != (v = find(q))) p[v] = u, --tt;
                    q = b[k]+m;
                    if (q<cc && h[q]>a[i] && u != (v = find(q))) p[v] = u, --tt;
                    q = b[k]%m>0 ? b[k]-1 : -1;
                    if (q>=0 && h[q]>a[i] && u != (v = find(q))) p[v] = u, --tt;
                    q = b[k]%m+1<m ? b[k]+1 : cc;
                    if (q<cc && h[q]>a[i] && u != (v = find(q))) p[v] = u, --tt;
                }
                c = j;
            }
            cnt[i] = tt;
        }
        for (int i=0; i<t; ++i) cout << cnt[i] << ' '; cout << endl;
    }
    return 0;
}