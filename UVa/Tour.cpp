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
    if (i >= j) return 0;
    if (d[i][j] > 0) return d[i][j];
    if (i == n-2) return d[i][j] = dis(i, j);
    for (int k=i+1; k<j; ++k)
        d[i][j] += dis(k-1, k);
    if (j == n-1) return d[i][j] += calc(j-1, j);
    double s = 0, m = DBL_MAX;
    for (int k=j+1; k<n; ++k) {
        double v = dis(j-1, k);
        if (k == n-1)
            m = min(m, v + s + dis(k-1, k));
        else for (int x = k+1; x<n; ++x) 
            m = min(m, v + calc(k, x) + dis(k-1, x) + s);
        s += dis(k-1, k);
    }
    return d[i][j] += m;
}

double calc() {
    if (n < 2) return 0;
    double m = DBL_MAX;
    for (int i=1; i<n; ++i) m = min(m, dis(0, i) + calc(0, i));
    return m;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(2);
    while (cin >> n) {
        memset(d, 0, sizeof(d)); 
        for (int i=0; i<n; ++i) cin >> p[i][0] >> p[i][1];
        cout << calc() << endl;
    }
    return 0;
}