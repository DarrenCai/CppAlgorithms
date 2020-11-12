/**
 * UVa1628
 * 送匹萨
 */

#include <iostream>
#include <map>
using namespace std;

#define N 100

map<int, int> d[N][N][2]; int p[N], e[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n; cin >> n;
    while (cin >> n) {
        short x = 0; int ans = 0, m = 0;
        for (short i=0; i<n; ++i) {
            cin >> p[i]; if (p[x] < 0 && p[i] > 0) x = i;
        }
        for (short i=0; i<n; ++i) cin >> e[i], m = max(e[i], m);
        if (x == 0) {
            if (p[0] > 0) {
                for (short i=0; i<n; ++i) ans += max(e[i]-p[i], 0);
            } else {
                for (short i=0; i<n; ++i) ans += max(e[i]+p[i], 0);
            }
        } else {
            for (short i=0; i<n; ++i) for (short j=i+1; j<n; ++j) d[i][j][0].clear(), d[i][j][1].clear();
            d[x][x][0][p[x]] = d[x][x][1][p[x]] = ans = max(e[x] - p[x], 0);
            ans = max(ans, d[x-1][x-1][0][-p[x-1]] = d[x-1][x-1][1][-p[x-1]] = max(e[x-1] + p[x-1], 0));
            for (short i=x-2; i>=0; --i) {
                int t = -p[i]; if (t > m) break;
                ans = max(ans, d[i][i][0][t] = d[i][i][1][t] = d[i+1][i+1][0][-p[i+1]] + max(e[i] + p[i], 0));
            }
            for (short i=x+1; i<n; ++i) {
                int t = p[i]; if (t > m) break;
                ans = max(ans, d[i][i][0][t] = d[i][i][1][t] = d[i-1][i-1][0][p[i-1]] + max(e[i] - p[i], 0));
            }
            for (short i=x-1; i>=0; --i) for (short j=x; j<n; ++j) {
                int t = 2*p[j]-p[i], v = 0;
                if (t <= m) {
                    for (short k=x; k<=j; ++k) v += max(e[k]-p[k], 0);
                    for (short k=x-1; k>=i; --k) v += max(e[k]-2*p[j]+p[k], 0);
                    ans = max(ans, d[i][j][0][t] = v);
                }
                t = p[j]-2*p[i]; v = 0;
                if (t <= m) {
                    for (short k=x-1; k>=i; --k) v += max(e[k]+p[k], 0);
                    for (short k=x; k<=j; ++k) v += max(e[k]-p[k]+2*p[i], 0);
                    ans = max(ans, d[i][j][1][t] = v);
                }
            }
            for (short i=x-1; i>=0; --i) for (short j=x; j<n; ++j) {
                map<int, int>::iterator it;
                for (it = d[i][j][0].begin(); it != d[i][j][0].end(); ++it) {
                    if (j+1 < n) {
                        int t = it->first + p[j+1] - p[i];
                        if (t <= m) {
                            int v = it->second + max(e[j+1]-t, 0); ans = max(ans, v);
                            if (d[i][j+1][1].count(t)) d[i][j+1][1][t] = max(d[i][j+1][1][t], v);
                            else d[i][j+1][1][t] = v;
                        }
                    }
                    if (i > 0) {
                        int t = it->first + p[i] - p[i-1];
                        if (t <= m) {
                            int v = it->second + max(e[i-1]-t, 0); ans = max(ans, v);
                            if (d[i-1][j][0].count(t)) d[i-1][j][0][t] = max(d[i-1][j][0][t], v);
                            else d[i-1][j][0][t] = v;
                        }
                    }
                }
                for (it = d[i][j][1].begin(); it != d[i][j][1].end(); ++it) {
                    if (j+1 < n) {
                        int t = it->first + p[j+1] - p[j];
                        if (t <= m) {
                            int v = it->second + max(e[j+1]-t, 0); ans = max(ans, v);
                            if (d[i][j+1][1].count(t)) d[i][j+1][1][t] = max(d[i][j+1][1][t], v);
                            else d[i][j+1][1][t] = v;
                        }
                    }
                    if (i > 0) {
                        int t = it->first + p[j] - p[i-1];
                        if (t <= m) {
                            int v = it->second + max(e[i-1]-t, 0); ans = max(ans, v);
                            if (d[i-1][j][0].count(t)) d[i-1][j][0][t] = max(d[i-1][j][0][t], v);
                            else d[i-1][j][0][t] = v;
                        }
                    }
                }
            }
        }
        cout << ans << endl;
    }
}