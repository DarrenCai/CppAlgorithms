/**
 * UVa11014
 * 制作水晶
 */

#include <iostream>
using namespace std;

#define N 100005
long long phi1[N] = {0}, phi2[N] = {0}; int n, kase = 0;

void solve() {
    n >>= 1;
    long long ans = 26;
    if (n > 1) ans += 48*phi1[n] + 24*phi2[n];
    cout << "Crystal " << ++kase << ": " << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    phi1[1] = 1;
    for (int i=2; i<N; ++i) {
        if (!phi1[i]) {
            phi1[i] = i-1;
            for (int j=2*i; j<N; j+=i) {
                if (!phi1[j]) phi1[j] = j;
                phi1[j] = phi1[j]/i*(i-1);
            }
        }
        phi2[i] = (i-1ll)*(i-1);
        for (int j=2; j*j <= i; ++j) if (i%j == 0) {
            int k = i/j;
            phi2[i] -= phi2[k];
            if (k > j) phi2[i] -= phi2[j];
        }
    }
    for (int i=3; i<N; ++i) phi1[i] += phi1[i-1], phi2[i] += phi2[i-1];
    while (cin>>n && n) solve();
    return 0;
}