/**
 * UVa10366
 * 龙头滴水
 */

#include <iostream>
#include <set>
using namespace std;

#define N 1010
int lh[N], rh[N];
struct cmpl {
    bool operator() (int a, int b) {
        return lh[a]>lh[b] || (lh[a]==lh[b] && a<b);
    }
};
struct cmpr {
    bool operator() (int a, int b) {
        return rh[a]>rh[b] || (rh[a]==rh[b] && a<b);
    }
};

long long calcl(set<int, cmpl>& sl, int x) {
    long long s = 0;
    while (!sl.empty()) {
        int li = *sl.begin(), xli = (li<<1)+1;
        s += (long long)lh[li] * (xli - x);
        for (int i = (x+1)>>1; i<=li; ++i) sl.erase(i);
        x = xli;
    }
    return s;
}

long long calcr(set<int, cmpr>& sr, int x) {
    long long s = 0;
    while (!sr.empty()) {
        int ri = *sr.begin(), xri = (ri<<1)+1;
        s += (long long)rh[ri] * (xri - x);
        for (int i = (x+1)>>1; i<=ri; ++i) sr.erase(i);
        x = xri;
    }
    return s;
}

long long calc(set<int, cmpl>& sl, set<int, cmpr>& sr, int xl=0, int xr=0) {
    int li = *sl.begin(), ri = *sr.begin();
    if (lh[li] == rh[ri]) {
        int xli = (li<<1)+1, xri = (ri<<1)+1;
        long long s = (long long)lh[li] * (xli-xl + xri-xr);
        for (int i = (xl+1)>>1; i<=li; ++i) sl.erase(i);
        for (int i = (xr+1)>>1; i<=ri; ++i) sr.erase(i);
        long long l = calcl(sl, xli), r = calcr(sr, xri);
        return s + (min(l, r)<<1);
    } else if (lh[li] < rh[ri]) {
        for (int i = (xr+1)>>1; i<=ri; ++i) if (rh[i] >= lh[li]) {
            if (rh[i] > lh[li])
                return (long long)lh[li] * ((i<<1)+1-xr) + calcl(sl, xl);
            else {
                int xli = (li<<1)+1, xri = (i<<1)+1;
                long long s = (long long)lh[li] * (xli-xl + xri-xr);
                for (int j = (xl+1)>>1; j<=li; ++j) sl.erase(j);
                long long l = calcl(sl, xli);
                for (int j=i+1; j<=ri; ++j) if (rh[j] > lh[li]) {
                    long long r = (long long)lh[li] * ((j<<1)+1 - xri);
                    return s + l + min(l, r);
                }
            }
        }
    } else {
        for (int i = (xl+1)>>1; i<=li; ++i) if (lh[i] >= rh[ri]) {
            if (lh[i] > rh[ri])
                return (long long)rh[ri] * ((i<<1)+1-xl) + calcr(sr, xr);
            else {
                int xli = (i<<1)+1, xri = (ri<<1)+1;
                long long s = (long long)rh[ri] * (xli-xl + xri-xr);
                for (int j = (xr+1)>>1; j<=ri; ++j) sr.erase(j);
                long long r = calcr(sr, xri);
                for (int j=i+1; j<=li; ++j) if (lh[j] > rh[ri]) {
                    long long l = (long long)rh[ri] * ((j<<1)+1 - xli);
                    return s + r + min(l, r);
                }
            }
        }
    }
    return 0;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int lx, rx;
    while (cin >> lx >> rx && lx && rx) {
        int l = (1-lx)>>1, r = (rx+1)>>1;
        set<int, cmpl> sl; set<int, cmpr> sr;
        for (int i=l-1; i>=0; --i) cin >> lh[i], sl.insert(i);
        for (int i=0; i<r; ++i) cin >> rh[i], sr.insert(i);
        cout << calc(sl, sr) << endl;
    }
    return 0;
}
