/**
 * UVa12325
 * 宝箱
 */

#include <iostream>

int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else {
        if (b & 1) return gcd(a >> 1, b);
        return gcd(a >> 1, b >> 1) << 1;
    } 
}

int n, s[2], v[2];
long long calc(short i, int m) {
    long long max = 0; short ii = i^1;
    for (int j=0; j<=m; ++j) {
        long long t = (long long)v[i]*j + (n-(long long)s[i]*j)/s[ii]*v[ii];
        if (t > max) max = t;
    }
    return max;
}

int main()
{
    using namespace std;
    short k=0, t; cin>>t;
    while (k < t) {
        cout << "Case #" << ++k << ": ";
        cin >> n >> s[0] >> v[0] >> s[1] >> v[1];
        int g = gcd(s[0], s[1]), ss1 = s[0]/g, ss2 = s[1]/g;
        long long lcm = (long long)ss1*s[1], ss1v2 = (long long)ss1*v[1], ss2v1 = (long long)ss2*v[0];
        int d = n/lcm; if (d) {-- d; n -= d*lcm;}
        long long va = ss1v2 > ss2v1 ? (long long)d*ss1v2 : (long long)d*ss2v1;
        int nds1 = n/s[0], nds2 = n/s[1];
        if (nds1 < nds2 && nds1 < ss1 && nds1 < ss2) {
            cout << va + calc(0, nds1) << endl;
        } else if (nds2 < nds1 && nds2 < ss1 && nds2 < ss2) {
            cout << va + calc(1, nds2) << endl;
        } else
            cout << va + ((ss1v2 == ss2v1 && ss1 > ss2) || ss1v2 > ss2v1 ? calc(0, ss2-1) : calc(1, ss1-1)) << endl;
    }
    return 0;
}