/**
 * UVa10692
 * 超大数取模
 * 广义欧拉定理（欧拉降幂）：b>=φ(m)时，a^b ≡ a^(b%φ(m)+φ(m)) mod m
 */

#include <iostream>
using namespace std;

#define M 10001
#define N 12
int phi[M] = {0}, a[N], m, n, kase = 0;

int mod(int a, int m) {
    return a<m ? a : a%m + m;
}

int pow_mod(int a, int n, int m) {
    int ans = 1;
    for (int k=n; k; k>>=1) {
        if (k & 1) ans = mod(ans*a, m);
        a = mod(a*a, m);
    }
    return ans;
}

int dfs(int i, int m) {
    if (i==n) return mod(a[i], m);
    int x = dfs(i+1, phi[m]), ans = pow_mod(a[i], x%phi[m], m);
    return x < phi[m] ? ans : mod(ans * pow_mod(a[i], phi[m], m), m);
}

void solve() {
    cin >> m >> n;
    for (int i=1; i<=n; ++i) cin >> a[i];
    cin.get();
    cout << "Case #" << ++kase << ": " << dfs(1, m) % m << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    phi[1] = 1;
    for(int i = 2; i < M; i++) if(!phi[i]) for(int j = i; j < M; j += i) {
        if(!phi[j]) phi[j] = j;
        phi[j] = phi[j] / i * (i-1);
    }
    while (cin.peek() != '#') solve();
    return 0;
}