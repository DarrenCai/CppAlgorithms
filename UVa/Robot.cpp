/**
 * UVa1622
 * 机器人
 */

#include <iostream>
#define min(a, b) (a<b ? a:b)
#define max(a, b) (a>b ? a:b)
#define ll long long
using namespace std;

ll calc(ll n, ll m, ll r1, ll r2) {
    ll s = 0;
    while (m && n && (r1 || r2)) {
        if (r1) {
            if (m < n || !r2) {
                s += m * n--; --r1;
            } else {
                s += n * m--; --r2;
            }
        } else {
            s += n * m--; --r2;
        }
    }
    return s;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ll n, m, k=0;
    while (cin >> n >> m && n && m) {
        ll cn, cs, cw, ce; cin >> cn >> cs >> cw >> ce;
        ll m1 = cn==cs ? cn<<1 : 1+(min(cn, cs)<<1);
        ll r1 = min(n-1, (cn==cs ? 0 : max(cn, cs) - min(cn, cs) - 1));
        ll m2 = cw==ce ? cw<<1 : 1+(min(cw, ce)<<1);
        ll r2 = min(m-1, (cw==ce ? 0 : max(cw, ce) - min(cw, ce) - 1));
        ll maxi = 0;
        if (m1) {
            if (m2) {
                long long n1 = n-1, l;
                maxi = (m1*n1+1)*m;
                while (n1 > (l = m2*(m-1)+1) && r1) {
                    maxi += m * n1--; --r1;
                }
                maxi += (m2 * (m-1) + 1) * n1 + calc(n1, m-1, r1, r2);
                long long s = (m2 * (n1=m-1) + 1) * n;
                while (n1 > (l = m1*(n-1)+1) && r2) {
                    s += n * n1--; --r2;
                }
                s += (m1 * (n-1) + 1) * n1 + calc(n-1, n1, r1, r2);
                if (s > maxi) maxi = s;
            } else {
                long long l;
                while (m > (l = m1*(n-1)+1) && r2) {
                    maxi += n * m--; --r2;
                }
                maxi += (m1 * --n + 1) * m;
                maxi += calc(n, m, r1, r2);
            }
        } else if (m2) {
            long long l;
            while (n > (l = m2*(m-1)+1) && r1) {
                maxi += m * n--; --r1;
            }
            maxi += (m2 * --m + 1) * n;
            maxi += calc(n, m, r1, r2);
        } else {
            maxi = calc(n, m, r1, r2);
        }
        cout << "Case " << ++k << ": " << maxi << endl;
    }
    return 0;
}