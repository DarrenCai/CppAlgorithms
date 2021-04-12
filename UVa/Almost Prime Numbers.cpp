/**
 * UVa10539
 * 几乎是素数
 */

#include <iostream>
using namespace std;

#define N 1000010
#define C 78600
bool flag[N] = {false}; int prim[C], c=0;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<1001; ++i) for (int j=i*i; j<N; j+=i) flag[j] = true;
    for (int i=2; i<N; ++i) if (!flag[i]) prim[c++] = i;
    short t; cin >> t;
    while (t--) {
        int s = 0; long long l, u; cin >> l >> u;
        for (int i=0; i<c; ++i) for (long long v = (long long)prim[i]*prim[i]; v<=u; v *= prim[i]) if (v >= l) ++s;
        cout << s << endl;
    }
    return 0;
}