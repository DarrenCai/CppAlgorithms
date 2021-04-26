/**
 * UVa1575
 * 因子
 */

#include <iostream>
using namespace std;

#define N 62
#define M 18
bool flag[N] = {false}; short prim[18], idx[N], d[N][M]={0}, cnt[M], c=0, a[N], cc, m; long long ans, mx = (1ull<<63)-1;

long long gcd(long long a, long long b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else {
        if (b & 1) return gcd(a >> 1, b);
        return gcd(a >> 1, b >> 1) << 1;
    }
}

bool check(short v) {
    for (short i=0; i<c && prim[i]<=v; ++i) if (cnt[i]) return false;
    __int128_t vv = 1; short j=0, mm = m;
    for (short i=0; i<cc; ++i, ++j) {
        for (short k=0; k<a[i]; ++k) if ((vv *= prim[j]) > mx) return true;
        mm -= a[i];
    }
    while (mm--) if ((vv *= prim[j++]) > mx) return true;
    ans = min(ans, (long long)vv);
    return true;
}

bool calc(short v, short t) {
    bool ok = t >= v;
    if (ok) for (short i=0; i<c && prim[i]<=v; ++i) {
        if (cnt[i] >= d[v][i]) {
            cnt[i] -= d[v][i];
        } else {
            for (short j=0; j<i; ++j) cnt[j] += d[v][j];
            ok = false;
            break;
        }
    }
    if (!ok && !flag[v] && cnt[idx[v]]) return false;
    if (ok) {
        a[cc++] = v;
        ok = check(v);
        ok = calc(v, t-v) || ok;
        --cc;
        for (short i=0; i<c && prim[i]<=v; ++i) cnt[i] += d[v][i];
    }
    return (v > 2 && (flag[v] || !cnt[idx[v]]) && calc(v-1, t)) || ok;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short i=2; i<8; ++i) if (!flag[i]) for (short j=i*i; j<=N; j+=i) flag[j] = true;
    for (short i=2; i<=N; ++i) if (!flag[i]) prim[idx[i] = c++] = i;
    d[2][0] = 1;
    for (short i=3, v, j; i<N; ++i) {
        for (j=0; j<c && prim[j]<=i; ++j) d[i][j] = d[i-1][j];
        for (v=i, j=0; j<c && prim[j]<v; ++j) if (v%prim[j] == 0)
            while (v%prim[j] == 0) ++ d[i][j], v /= prim[j];
        if (v > 1) ++ d[i][idx[v]];
    }
    long long n;
    while (cin >> n) {
        cout << n << ' ';
        for (short i=0; i<c; ++i) cnt[i] = 0;
        ans = n==1 ? 2 : mx;
        for (m=1; m<=N; ++m) {
            short g = gcd(m, n), v = m;
            if (n > 1) n /= g, v = m/g;
            for (short i=0; i<c && prim[i]<=v; ++i) if (v%prim[i] == 0)
                while (v%prim[i] == 0) ++ cnt[i], v /= prim[i];
            if (n == 1) {
                if (m > 1) {
                    if (!flag[m] && cnt[idx[m]]) continue;
                    cc = 0;
                    if (!check(m-1)) calc(m-1, m);
                } else break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
