/**
 * UVa1252
 * 20个问题
 */

#include <iostream>
#include <cstring>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define max(a, b) (a>b ? a:b)
#define M 11
#define N 128
short m, n, p[N], d[1<<M][1<<M], cnt[1<<M][1<<M]; char buf[M+2];

short dp(short s, short a) {
    if (d[s][a] > -1) return d[s][a];
    if (cnt[s][a] <= 1) return d[s][a] = 0;
    if (cnt[s][a] == 2) return d[s][a] = 1;

    d[s][a] = m;
    for (short k=0, v=1; k<m; ++k, v<<=1) if ((s & v) == 0)
        d[s][a] = min(d[s][a], 1 + max(dp(s | v, a | v), dp(s | v, a)));
    return d[s][a];
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> m >> n && m) {
        cin.get();
        for (short i=0; i<n; ++i) {
            cin.getline(buf, sizeof(buf)); p[i] = 0;
            for (short j=0; j<m; ++j) p[i] = (p[i] << 1) | buf[j]-'0';
        }
        memset(cnt, 0, sizeof(cnt)); memset(d, -1, sizeof(d));
        for (short s=(1<<m)-1; s>=0; --s) for (short j=0; j<n; ++j) ++cnt[s][s & p[j]];
        cout << dp(0, 0) << endl;
    }
    return 0;
}