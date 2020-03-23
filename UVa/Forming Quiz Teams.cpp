/**
 * UVa10911
 * 最优配对问题
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define INF 2e4
#define N 20
double d[1<<N]={0}; short x[N], y[N], n, k=0; char name[30];

double dis(short i, short j) {
    short dx = x[i] - x[j], dy = y[i] - y[j];
    return sqrt(double(dx * dx + dy * dy));
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    while (cin >> n && n) {
        n <<= 1;
        for (short i=0; i<n; ++i) cin >> name >> x[i] >> y[i];
        for (int s=1, i; s < (1<<n); ++s) {
            d[s] = INF;
            for (i=0; i<n; ++i) if (s & (1<<i)) break;
            for (int j=i+1; (1<<j) < s; ++j) if ((1<<j) & s) {
                d[s] = min(d[s], d[s ^ (1<<i) ^ (1<<j)] + dis(i, j));
            }
        }
        cout << "Case " << ++k << ": " << d[(1<<n)-1] << endl;
    }
    return 0;
}