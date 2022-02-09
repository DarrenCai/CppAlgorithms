/**
 * UVa11210
 * 中国⿇将
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define N 35
enum {_, t1, t2, t3, t4, t5, t6, t7, t8, t9, s1, s2, s3, s4, s5, s6, s7, s8, s9,
        w1, w2, w3, w4, w5, w6, w7, w8, w9, dong, nan, xi, bei, zhong, fa, bai};
char mj[][6] = {"DONG", "NAN", "XI", "BEI", "ZHONG", "FA", "BAI"};
short p[14], pp[13], cnt[N], cc[N], t[N], m; char s[6];

short get() {
    cin >> s;
    if (s[0] == '0') return _;
    if (s[1] == 'O') return dong;
    if (s[0] == 'N') return nan;
    if (s[1] == 'I') return xi;
    if (s[1] == 'E') return bei;
    if (s[1] == 'H') return zhong;
    if (s[0] == 'F') return fa;
    if (s[0] == 'B') return bai;
    if (s[1] == 'T') return t1 + s[0]-'1';
    if (s[1] == 'S') return s1 + s[0]-'1';
    return w1 + s[0]-'1';
}

bool hu(short s = 0, short c = 0, bool ja = false) {
    if (c==4 && ja) return true;
    if (cnt[p[s]] < 1) return hu(s+1, c, ja);
    if (!ja && cnt[p[s]] >= 2) {
        cnt[p[s]] -= 2;
        if (hu(s, c, true)) return true;
        cnt[p[s]] += 2;
    }
    if (cnt[p[s]] >= 3) {
        cnt[p[s]] -= 3;
        if (hu(s, c+1, ja)) return true;
        cnt[p[s]] += 3;
    }
    short cc = cnt[p[s]], t = (p[s]-1)/9;
    if (p[s]>w9 || s>m-3 || cnt[p[s+1]]<cc || cnt[p[s+2]]<cc ||
        p[s+1] > p[s]+1 || p[s+2] > p[s]+2 || (p[s+1]-1)/9 != t || (p[s+2]-1)/9 != t) return false;
    cnt[p[s]] -= cc; cnt[p[s+1]] -= cc; cnt[p[s+2]] -= cc;
    if (hu(s+1, c+cc, ja)) return true;
    cnt[p[s]] += cc; cnt[p[s+1]] += cc; cnt[p[s+2]] += cc;
    return false;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int kase = 0;
    while (true) {
        memset(cc, 0, sizeof(cc));
        for (short i=0; i<13; ++i) {
            short m = get();
            if (m < t1) return 0;
            ++cc[pp[i] = m];
        }
        short c = 0;
        for (short i=1; i<N; ++i) if (cc[i] < 4) {
            memcpy(p, pp, sizeof(pp)); memcpy(cnt, cc, sizeof(cc));
            ++cnt[p[13] = i]; sort(p, p+14); m = unique(p, p+14) - p;
            if (hu()) t[c++] = i;
        }
        if (c > 0) {
            cout << "Case " << ++kase << ':';
            for (short i=0; i<c; ++i) {
                if (t[i] < dong) {
                    cout << ' ' << (t[i]<s1 ? t[i] : (t[i]<w1 ? t[i]-t9 : t[i]-s9)) << (t[i]<s1 ? 'T' : (t[i]<w1 ? 'S' : 'W'));
                } else cout << ' ' << mj[t[i]-dong];
            }
            cout << endl;
        } else cout << "Case " << ++kase << ": Not ready" << endl;
    }
    return 0;
}