/**
 * UVa11802
 */

#include <iostream>
using namespace std;

#define M 1000000007
#define N 550
#define S 24

short prim[N], c = 0; bool flag[N] = {false}; long long cnt[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short i=2; i<S; ++i) for (short j=i*i; j<N; j+=i) flag[j] = true;
    for (short i=2; i<N; ++i) if (!flag[i]) prim[c++] = i;
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        short cc = 0; long long n, k; cin >> n >> k;
        for (short i=0; i<c; ++i, ++cc) {
            long long v = n/prim[i]; cnt[i] = v;
            while (v >= prim[i]) cnt[i] += (v/=prim[i]);
            if (cnt[i] < k) break;
        }
        long long v1 = 1, v2 = 1;
        for (short i=0; i<cc; ++i) {
            long long a = cnt[i]/k, b = cnt[i] / (k+1);
            v1 = (a+1)%M*v1%M;
            v2 = (b+1)%M*v2%M;
        }
        cout << "Case " << kase << ": " << (v1-v2+M)%M << endl;
    }
    return 0;
}