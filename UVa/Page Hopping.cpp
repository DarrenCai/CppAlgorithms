/**
 * UVa821
 * 网页跳跃
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 110
int d[N][N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(3);
    short a, b; int kase = 0;
    while (cin>>a>>b && a) {
        for (short i=1; i<N; ++i) for (short j=i+1; j<N; ++j) d[i][j] = d[j][i] = N;
        short n = max(a, b);
        do {
            d[a][b] = 1;
            n = max(max(n, a), b);
        } while (cin>>a>>b && a);
        for (short k=1; k<=n; ++k) for (short i=1; i<=n; ++i) for (short j=1; j<=n; ++j) if (i!=j && i!=k && j!=k)
            d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
        double s = 0; int c = 0;
        for (short i=1; i<=n; ++i) for (short j=1; j<=n; ++j) if (i!=j && d[i][j]<N) s += d[i][j], ++c;
        cout << "Case " << ++kase << ": average length between pages = " << s/c << " clicks" << endl;
    }
    return 0;
}