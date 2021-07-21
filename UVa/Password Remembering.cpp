/**
 * UVa12212
 * 记住密码
 */

#include <iostream>
using namespace std;

#define ULL unsigned long long
__uint128_t p[21];

short bits(ULL x) {
    short l = 1;
    while (x > 9) x/=10, ++l;
    return l;
}

__uint128_t reverse(ULL x, short l) {
    __uint128_t y = 0;
    for (short i=--l; i>=0; --i) y += x/p[i]%10*p[l-i];
    return y;
}

ULL calc(ULL a, ULL b, short l) {
    if (l-- == 1) return 10-max(a, b);
    short a0 = a/p[l];
    return (p[l]-b/10)*(9-a0) - max(int(b%10)-a0-1, 0) + calc(a%p[l], (b+9-a0)/10, l);
}

ULL calc(ULL a1, ULL a2, ULL b1, ULL b2, short l) {
    ULL d; bool same[21]; same[l] = true;
    for (short i=l-1; i>=0; --i) same[i] = same[i+1] && a1/p[i]%10 == a2/p[i]%10;
    __uint128_t x = reverse(a1, l); d = x>=b1 && x<=b2;
    if (!same[0]) x = reverse(a2, l), d += x>=b1 && x<=b2;
    for (short i=1; i<=l; ++i) {
        x = reverse(a1/p[i], l-i);
        for (short j=a1/p[i-1]%10+1, jj=same[i] ? a2/p[i-1]%10 : 10; j<jj; ++j) {
            short l1 = l-i, l2 = l1+1; __uint128_t y = j*p[l1] + x;
            if (y > b2) break;
            ULL a = y>=b1 ? 0 : ((b1-y)/p[l2] + ((b1-y)%p[l2] ? 1 : 0)), b = (b2-y)/p[l2];
            d += b>=a ? b-a+1 : 0;
        }
        if (!same[i]) {
            x = reverse(a2/p[i], l-i);
            for (short j=0, jj=a2/p[i-1]%10; j<jj; ++j) {
                short l1 = l-i, l2 = l1+1; __uint128_t y = j*p[l1] + x;
                if (y > b2) break;
                ULL a = y>=b1 ? 0 : ((b1-y)/p[l2] + ((b1-y)%p[l2] ? 1 : 0)), b = (b2-y)/p[l2];
                d += b>=a ? b-a+1 : 0;
            }
        }
    }
    return d;
}

ULL calc(ULL a, ULL b) {
    if (b < a) return 0;
    short la = bits(a), lb = bits(b);
    if (la < lb) {
        short a0 = a/p[--la], b0 = b/p[--lb];
        ULL cnt = la==0 ? 10-a0 : (p[la]-a/10)*(9-a0) - max(int(a%10)-a0-1, 0) + calc(a%p[la], (a+9-a0)/10, la);
        short l = la+1, t = lb-l;
        if (t) cnt += (p[t]-1)*p[l] - t * (a/10*9 + max(int(a%10)-1, 0));
        for (short i=1; i<b0; ++i) cnt += (b-i)/10 - (a+9-i)/10 + 1;
        return cnt + calc(0, b%p[lb], (a+9-b0)/10, (b-b0)/10, lb);
    }
    return calc(a, b, a, b, la);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    p[0] = 1; for (short i=1; i<21; ++i) p[i] = 10*p[i-1];
    short t; cin >> t;
    for (short kase=1; kase<=t; ++kase) {
        ULL a, b; cin >> a >> b;
        cout << "Case " << kase << ": " << calc(a, b) << endl;
    }
    return 0;
}