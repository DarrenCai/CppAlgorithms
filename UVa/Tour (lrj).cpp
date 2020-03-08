/**
 * UVa1347
 * 旅行
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <cfloat>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define N 2010
int p[N][2], n; double d[N][N];

double dis(int i, int j) {
    int dx = p[i][0]-p[j][0], dy = p[i][1]-p[j][1];
    dx *= dx; dy *= dy;
    return sqrt(double(dx) + double(dy));
}

double calc(int i, int j) {
    if (d[i][j] > 0) return d[i][j];
    if (i == n-1) return d[i][j] = dis(i, n) + dis(j,n);
    return d[i][j] = min(calc(i+1,j) + dis(i,i+1), calc(i+1,i) + dis(j,i+1));
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    while (cin >> n) {
        memset(d, 0, sizeof(d)); 
        for (int i=1; i<=n; ++i) cin >> p[i][0] >> p[i][1];
        cout << dis(1,2) + calc(2,1) << endl;
    }
    return 0;
}