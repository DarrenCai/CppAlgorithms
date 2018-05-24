/**
 * UVa12558
 * 埃及分数问
 */

#include <iostream>
#include <vector>
using namespace std;

#define LL long long
short s[5], k, d; vector<LL> ans, tmp;

LL gcd(LL a, LL b) {
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

// LL gcd(LL a, LL b) {
//     return a ? gcd(b%a, a) : b;
// }

bool ok(LL i) {
    for (short j=0; i<=1000 && j<k; ++j)
        if (s[j] == i) return false;
    return true;
}

bool IDDFS(LL a, LL b, short cur=0, LL l=2) {
    if (cur+2 == d) {
        for (LL t=b<<1, i=max(l, (b+a-1)/a); a*i < t; ++i) {
            if (ok(i) && b*i % (a*i-b) == 0) {
                LL bb = b*i/(a*i-b);
                if (ok(bb)) {
                    if (tmp.size() > cur) tmp[cur] = i;
                    else tmp.push_back(i);
                    if (tmp.size() > cur+1) tmp[cur+1] = bb;
                    else tmp.push_back(bb);
                    if (ans.size() == 0) {
                        ans = tmp;
                    } else {
                        bool better = false;
                        for (short j=d-1; !better && j>=0; --j)
                            if (tmp[j]<ans[j]) better = true;
                            else if (tmp[j]>ans[j]) break;
                        if (better) ans = tmp;
                    }
                }
            }
        }
    } else {
        for (LL t=b*(d-cur), i=max(l, (b+a-1)/a); a*i < t; ++i) {
            if (ok(i)) {
                LL aa = a*i-b, bb = b*i;
                LL c = gcd(aa, bb);
                aa /= c; bb /= c;
                if (tmp.size() > cur) tmp[cur] = i;
                else tmp.push_back(i);
                IDDFS(aa, bb, cur+1, i+1);
            }
        }
    }
    return ans.size()>0;
}

int main()
{
    int t; cin>>t;
    for (int i=1; i<=t; ++i) {
        short a, b; cin>>a>>b>>k; d = 2;
        for (char j=0; j<k; ++j) cin >> s[j];
        while (!IDDFS(a, b)) ++ d;
        cout << "Case " << i << ": " << a << '/' << b << "=1/" << ans[0];
        for (short j=1; j<d; ++j) cout << "+1/" << ans[j];
        cout << endl; tmp.clear(); ans.clear();
    }
    return 0;
}