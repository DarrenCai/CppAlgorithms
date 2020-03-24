/**
 * ICPC Archive Volumes :: Volume 22 (2200-2299)
 * Regionals 2001 >> Africa/Middle East - South Africa
 * 2243 - Channel Allocation
 */

#include <iostream>
#include <cstring>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define N 30
bool g[N][N]; char s[N]; short c[N], n;


int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) {
        memset(g, 0, sizeof(g)); memset(c, 0, sizeof(c));
        for (short i=0; i<n; ++i) {
            cin >> s;
            short u = s[0]-'A';
            for (char *p=s+2; *p; ++p) g[u][*p - 'A'] = true;
        }
        short ans = 1;
        for (short i=0, color; i<n; ++i) {
            for (color=1; color <= ans; ++color) {
                bool ok = true;
                for (short j=0; j<n; ++j) if (g[i][j] && c[j] == color) {
                    ok = false; break;
                }
                if (ok) break;
            }
            c[i] = color;
            if (color > ans) ans = color;
        }
        cout << ans << (ans==1 ? " channel" : " channels") << " needed." << endl;
    }
    return 0;
}