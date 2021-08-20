/**
 * UVa10837
 * 一个研究课题
 */

#include <iostream>
#include <cmath>
using namespace std;

#define N 1000010
bool flag[N] = {false}; int prim[78510], c = 0, d[20010], t;

int euler_phi(int n) {
    int m = sqrt(n+0.5);
    int ans = n;
    for(int i = 2; i <= m; i++) if(n % i == 0) {
        ans = ans / i * (i-1);
        while(n % i == 0) n /= i;
    }
    if(n > 1) ans = ans / n * (n-1);
    return ans;
}

bool isPrim(int n) {
    if (n < N) return !flag[n];
    int m = sqrt(n+.5);
    for (int i=0; i<c && prim[i]<=m; ++i) if (n%prim[i] == 0) return false;
    return true;
}

int solve(int x, int p, int cc, int n) {
    if (euler_phi(x*cc) == n) return x*cc;
    if (isPrim(x+1) && euler_phi(cc*(x+1)) == n) return cc*(x+1);
    int ans = 200000001;
    for (int i=p; i<t && d[i]<=x; ++i) if (x%d[i]==0) ans = min(ans, solve(x/d[i], i+1, (d[i]+1)*cc, n));
    return ans;
}

int solve(int n) {
    if (n == 1) return 1;
    t = 0;
    int m = sqrt(n+.5)+1;
    for (int i=0; i<c && prim[i]<=m; ++i) if (n%(prim[i]-1)==0) d[t++] = prim[i]-1;
    for (int i=m; i>1; --i) if (n%i==0 && n/i>=m && isPrim(n/i+1)) d[t++] = n/i;
    return solve(n, 0, 1, n);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (int i=2; i<1001; ++i) if (!flag[i]) for (int j=i*i; j<N; j+=i) flag[j] = true;
    for (int i=2; i<N; ++i) if (!flag[i]) prim[c++] = i;
    bool f = isPrim(257);
    int n, kase = 0;
    while (cin>>n && n) cout << "Case " << ++kase << ": " << n << ' ' << solve(n) << endl;
    return 0;
}