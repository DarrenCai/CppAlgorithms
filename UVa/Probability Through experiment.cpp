/**
 * UVa12535
 * 实验法计算概率
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 20010
int s[N]; short l[N], u[N], n;

long long calc() {
    long long cnt = 0, cc= 0;
    short h = 0, t = 0;
    for (short i=0; i<n && s[i]<180000; ++i) {
        if (i) {
            while (h<t && l[h]<u[i]) {
                cc -= l[h] < u[i-1] ? 0 : l[h]+1 - u[i-1];
                ++h;
            }
            if (u[i]>u[i-1]) cc -= (t-h) * (u[i]-u[i-1]);
        }
        while (t<n && s[t]<s[i]+180000) {
            short p = lower_bound(s, s+n, s[t]+180000) - s;
            l[t] = p-1;
            u[t] = s[p] == s[t]+180000 ? p+1 : p;
            cc += l[t] < u[i] ? 0 : l[t]+1 - u[i];
            ++ t;
        }
        cnt += cc;
    }
    return cnt;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short r, kase = 0;
    while (cin>>n>>r && (n || r)) {
        for (short i=0; i<n; ++i) {
            double v; cin >> v;
            s[i] = v*1000+.5;
        }
        sort(s, s+n);
        cout << "Case " << ++kase << ": " << calc() << endl;
    }
    return 0;
}