/**
 * UVa12588
 * 团体数学竞赛
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 6
#define M 36
#define T 201000
double p[N][M], d[T]; short n, m, k, kk, b, kase, visit[T] = {0}; bool q[M];

void decode(int x, short (&a)[N]) {
    for (short i=0; i<n; ++i) a[i] = x%b, x /= b;
}

int encode(const short (&a)[N], bool f = true) {
    int x = 0;
    for (short i=n-1; i>=0; --i) x = x*b+a[i];
    return (x<<1) + f;
}

double dfs(int x) {
    bool f = x&1; short tp[N], t=0, z=0; decode(x>>1, tp);
    for (short i=0; i<n; ++i) t += tp[i], z += tp[i]==k;
    if (t == m) return d[x] = 0.;
    if (visit[x] == kase) return d[x];
    visit[x] = kase; d[x] = 0.;
    for (short i=0; i<n; ++i) if (tp[i]+1<k || (z<kk && tp[i]+1==k)) {
        ++tp[i];
        double np = q[t+1] && f ? 0. : p[i][t+1];
        d[x] = max(d[x], np*(1+dfs(encode(tp, false))) + (1-np)*dfs(encode(tp)));
        --tp[i];
    }
    return d[x];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    short t; cin >> t;
    for (kase=1; kase<=t; ++kase) {
        cin >> n >> m >> k;
        for (short i=1; i<=m; ++i) q[i] = false;
        for (short i=0; i<k; ++i) {
            short v; cin >> v; q[v] = true;
        }
        for (short i=0; i<n; ++i) for (short j=1; j<=m; ++j) cin >> p[i][j];
        k = (m+n-1)/n; b = k+1; kk = (m-1)%n+1;
        cout << "Case " << kase << ": " << dfs(0) << endl;
    }
    return 0;
}