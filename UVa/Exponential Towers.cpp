/**
 * UVa1656
 * 指数塔
 */

#include <iostream>
#include <cmath>
using namespace std;

#define N 98
#define M 124610
int p[M], prim[30], t = 0, cc[30]; bool flag[N] = {false}; long long d[M];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<10; ++i) if (!flag[i]) for (int j=i*i; j<N; j+=i) flag[j] = true;
    for (int i=2; i<N; ++i) if (!flag[i]) prim[t++] = i;
    for (int i=2; i<M; ++i) {
        d[i] = p[i] = 1;
        for (int j=16; j>1; --j) {
            int x = pow(i+.5l, 1.l/j);
            if (pow(1.l*x, 1.l*j) == i) {
                p[i] = j;
                break;
            }
        }
        for (int j=2; j<=p[i]; ++j) if (p[i]%j == 0) d[i] += d[j];
    }
    int a, b, c;
    while (cin>>a) {
        cin.get(); cin >> b; cin.get(); cin >> c;
        int cnt = 0, pp = p[a], m = sqrt(max(pp, b)+.5), mx = 1;
        for (int i=0; i<t && prim[i] <= m; ++i) {
            if (b%prim[i] == 0) {
                cc[cnt] = 0;
                while (b%prim[i] == 0) b /= prim[i], cc[cnt] += c;
                if (pp%prim[i] == 0) while (pp%prim[i] == 0) pp /= prim[i], ++cc[cnt];
                ++ cnt;
            } else if (pp%prim[i] == 0) {
                cc[cnt] = 0;
                if (pp%prim[i] == 0) while (pp%prim[i] == 0) pp /= prim[i], ++cc[cnt];
                ++ cnt;
            } 
        }
        if (b > 1) {
            cc[cnt] = c;
            if (pp == b) ++cc[cnt];
            ++ cnt;
        }
        for (int i=0; i<cnt; ++i) mx = max(mx, cc[i]);
        long long ans = 0;
        for (int i=2; i<=mx; ++i) {
            long long t = 1;
            for (int j=0; j<cnt; ++j) t *= cc[j]/i + 1;
            ans += (t-1)*d[i];
        }
        cout << ans << endl;
    }
    return 0;
}