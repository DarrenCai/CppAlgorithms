/**
 * UVa10214
 * 树林里的树
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 2010
#define K 45
bool flag[N]={false}; short phi[N], g[N][K], t[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short i=2; i<K; ++i) if (!flag[i])
        for (int j=i*i; j<N; j+=i) flag[j] = true;
    for(int i=2; i<N; ++i) phi[i] = 0;
    phi[1] = 1;
    for(int i=2; i<N; ++i) {
        if(!phi[i]) for(int j=i; j<N; j += i) {
            if(!phi[j]) phi[j] = j;
            phi[j] = phi[j]/i*(i-1);
        }
        if (flag[i]) {
            t[i] = 0;
            short n = i;
            for (short j=2; j<n; ++j) if (!flag[j] && n%j==0) {
                g[i][t[i]++] = j;
                while (n%j == 0) n /= j;
            }
            if (n > 1) g[i][t[i]++] = n;
        }
    }
    cout << fixed << setprecision(7);
    int a, b;
    while (cin>>a>>b && a && b) {
        if (a > b) {
            int t = a; a = b; b = t;
        }
        long long s = b+1;
        for (short i=2; i<=a; ++i) {
            if (flag[i]) {
                s += b/i*phi[i];
                for (int j = b/i*i+1; j<=b; ++j) {
                    bool f = false;
                    for (short k=0; k<t[i]; ++k) if (j%g[i][k]==0) {
                        f = true;
                        break;
                    }
                    if (!f) ++s;
                }
            } else s += b - b/i;
        }
        cout << s/(1.*a*b + .5*a + .5*b) << endl;
    }
    return 0;
}