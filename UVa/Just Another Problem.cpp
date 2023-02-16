/**
 * UVa11490
 * 虚张声势
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define M 100000007
#define N 410000
#define P 641
long long a[N], prim[N], s; int t = 0, n; bool f[N] = {false};

void dfs(int cur, int p, long long v) {
    if (v <= 6*cur) return;
    if ((v-6*cur)%7 == 0) a[n++] = (v-6*cur)/7;
    if (v%prim[p] == 0) dfs(cur*prim[p], p, v / prim[p]);
    while (++p < t) {
        if (6*cur*prim[p] >= v/prim[p]) break;
        if (v%prim[p] == 0) dfs(cur*prim[p], p, v / prim[p]);
    }
}

void solve() {
    dfs(1, n = 0, s);
    sort(a, a+n);
    if (!n) cout << "No Solution Possible" << endl;
    while (n--) {
        long long d = a[n] % M;
        cout << "Possible Missing Soldiers = " << 2*d*d % M << endl;
    }
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<P; ++i) if (!f[i]) for (int j=i*i; j<N; j+=i) f[j] = true;
    for (int i=2; i<N; ++i) if (!f[i]) prim[t++] = i;
    ios::sync_with_stdio(false);
    while (cin>>s && s) solve();
    return 0;
}