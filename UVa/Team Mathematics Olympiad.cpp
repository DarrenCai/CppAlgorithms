/**
 * UVa12588
 * 团体数学竞赛
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 6
#define M 36
#define T 235300 // 2*(7^6) + 2
double p[N][M], d[T]; short n, b; bool q[M];

void decode(int x, short (&a)[N]) {
    for (short i=0; i<n; ++i) a[i] = x%b, x /= b;
}

int encode(const short (&a)[N], bool f = true) {
    int x = 0;
    for (short i=n-1; i>=0; --i) x = x*b+a[i];
    return (x<<1) + f;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    short t, m, k; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        cin >> n >> m >> k;
        for (short i=1; i<=m; ++i) q[i] = false;
        for (short i=0; i<k; ++i) {
            short v; cin >> v; q[v] = true;
        }
        for (short i=0; i<n; ++i) for (short j=1; j<=m; ++j) cin >> p[i][j];
        short kk = (m-1)%n+1; k = (m+n-1)/n; b = k+1;
        int x = 0; for (short i=0; i<n; ++i) x = x*(k+1) + k; x = (x<<1)+1;
        while (x >= 0) {
            d[x] = 0.;
            bool f = x&1; short tp[N], t=0, z = 0; decode(x>>1, tp);
            for (short i=0; i<n; ++i) t += tp[i], z += tp[i]==k;
            if (t < m && z <= kk) {
                if (!q[t+1] && !f) {
                    d[x] = d[x+1];
                } else for (short i=0; i<n; ++i) if (tp[i]+1<k || (z<kk && tp[i]+1==k)) {
                    ++tp[i];
                    double np = q[t+1] && f ? 0. : p[i][t+1];
                    d[x] = max(d[x], np*(1+d[encode(tp, false)]) + (1-np)*d[encode(tp)]);
                    --tp[i];
                }
            }
            --x;
        }
        cout << "Case " << kase << ": " << d[0] << endl;
    }
    return 0;
}