/**
 * UVa11582
 * 巨大的斐波那契数!
 */

#include <iostream>
using namespace std;

#define N 1100
short f[N*N];

int pow(short a, unsigned long long n, int m) {
    if (a == 0) return 0;
    if (n == 0) return 1%m;
    long long ans = pow(a, n>>1, m);
    ans = ans*ans%m;
    return n&1 ? (ans*a)%m : ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    f[0] = 0;
    short t; cin >> t;
    while (t--) {
        unsigned long long a, b; short n; cin >> a >> b >> n;
        f[1] = 1%n;
        for (int m=n*n, i=0; i++ < m;) {
            f[i+1] = (f[i] + f[i-1]) % n;
            if (f[i]==f[0] && f[i+1]==f[1]) {
                cout << f[pow(a%i, b, i)] << endl;
                break;
            }
        }
    }
    return 0;
}