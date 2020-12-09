/**
 * UVa1633
 * 禁止的回文子串
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 410
#define K 12
#define M 1000000007

int p[N], f[N], d[N][1<<K], n, k; bool s[1<<K][K];

int dp(short i, int b) {
    int &ref = d[i][b], v;
    if (ref > -1) return ref;
    if (i == n) return ref = !s[b][k];
    ref = 0;
    if (!s[v = b<<1][k+1] && !s[v &= ~(1<<k)][k]) {
        ref += dp(i+1, v);
        if (ref >= M) ref -= M;
    }
    if (!s[v = b<<1 | 1][k+1] && !s[v &= ~(1<<k)][k]) {
        ref += dp(i+1, v);
        if (ref >= M) ref -= M;
    }
    return ref;
}

int solve(short n, short k) {
    if (n < k) return p[n];
    if (n == k) {
        int t = p[n] - f[n];
        return t >= 0 ? t : t+M;
    }
    memset(d, -1, sizeof(d));
    int t = 0;
    for (int b = (1<<k)-2; b>0; --b) if (!s[b][k]) {
        t += dp(k, b);
        if (t >= M) t -= M;
    }
    return t;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    p[0] = 1;
    for (int i=1; i<N; ++i) {
        p[i] = p[i-1]<<1; f[i] = p[(i+1)>>1];
        if (p[i] >= M) p[i] -= M;
    }
    for (int k=1; k<K; ++k) for (int b = (1<<k)-1; b >= 0; --b) {
        if (k==1) s[b][k] = true;
        else if (k==2) s[b][k] = b==0 || b==3;
        else s[b][k] = ((b&1) == b>>k-1) && s[(b & ~(1<<k-1))>>1][k-2];
    }
    short t; cin >> t;
    while (t--) {
        cin >> n >> k;
        cout << solve(n, k) << endl;
    }
    return 0;
}