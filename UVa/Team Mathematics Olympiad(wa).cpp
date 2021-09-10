/**
 * UVa12588
 * 团体数学竞赛
 */

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#define N 6
#define M 36
#define T 46700
double p[N][M], d[M][T]; short n, m, k, b, kk, l[M], r[M], s[T][N], tp[N]; int e[M][T], cnt[M];

bool check(const short (&a)[N], bool b) {
    short c = 0;
    for (short i=0; i<n; ++i) {
        if (a[i]>k || (b && a[i]<k-1)) return false;
        if (a[i] == k) ++c;
    }
    return c <= kk;
}

void decode(int x) {
    int y = x; short c = 0;
    for (short i=0; i<n; ++i) s[x][i] = y%b, y /= b, c += s[x][i];
    if (check(s[x], c==m)) e[c][cnt[c]++] = x;
}

int encode(const short (&a)[N]) {
    int x = 0;
    for (short i=n-1; i>=0; --i) x = x*b+a[i];
    return x;
}

double solve() {
    k = (m+n-1)/n; kk = (m-1)%n+1; b = k+1;
    memset(cnt, 0, sizeof(cnt));
    memset(d, 0, sizeof(d));
    int x = 0; for (short i=0; i<n; ++i) x = x*b+k;
    while(x>=0) decode(x--);
    for (short i=m; i>0; --i) {
        if (l[i]==i && r[i]==i) {
            short ii = m-i+1;
            for (int j=0; j<cnt[ii]; ++j) {
                short (&a)[N] = s[e[ii][j]];
                for (short r=0; r<n; ++r) if (a[r]) {
                    --a[r];
                    d[i][e[ii][j]] = max(d[i][e[ii][j]], p[r][i]+d[i+1][encode(a)]);
                    ++a[r];
                }
            }
        } else {
            short ii = r[i]-i+1;
            for (int j=0; j<cnt[ii]; ++j) {
                short (&a)[N] = s[e[ii][j]];
                for (short r=0; r<n; ++r) if (a[r]) {
                    --a[r];
                    d[i][e[ii][j]] = max(d[i][e[ii][j]], p[r][i]+p[r][i]*d[i+1][encode(a)]);
                    ++a[r];
                }
            }
            if (l[i]==i && r[i]<m) {
                short c = m-r[i];
                for (int j=0; j<cnt[ii]; ++j) {
                    short (&a)[N] = s[e[ii][j]];
                    for (int t=0; t<cnt[c]; ++t) {
                        short (&b)[N] = s[e[c][t]];
                        for (short r=0; r<n; ++r) tp[r] = a[r]+b[r];
                        if (check(tp, i==1)) {
                            double& ref = d[i][encode(tp)];
                            ref = max(ref, d[i][e[ii][j]] + d[r[i]+1][e[c][t]]);
                        }
                    }
                }
            }
        }
    }
    double ans = 0.;
    for (int i=0; i<cnt[m]; ++i) ans = max(ans, d[1][e[m][i]]);
    return ans;
}

int main() {
    // freopen("in.1.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    short t, kase; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        cin >> n >> m >> k;
        for (short i=1; i<=m; ++i) l[i] = r[i] = i;
        for (short i=0; i<k; ++i) {
            short v; cin >> v;
            r[v-1] = v;
            l[v] = l[v-1];
        }
        for (short i=m-1; i>0; --i) r[i] = r[r[i]];
        for (short i=0; i<n; ++i) for (short j=1; j<=m; ++j) cin >> p[i][j];
        cout << "Case " << kase << ": " << solve() << endl;
    }
    return 0;
}