/**
 * UVa1282
 * Fibonacci单词
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define T 26
#define N 105
#define M 100050
#define ULL unsigned long long

ULL d[N]; char t[M<<1], s[M<<1], p[M]; short n; int f[T], nxt[M], tLen, pLen;

void getNext() {
    nxt[0] = -1;
    int i = 0, j = -1;
    while (i < pLen) {
        if (j==-1 || p[i] == p[j]) {
            if (p[++i] == p[++j]) {
                nxt[i] = nxt[j];
            } else nxt[i] = j;
        } else j = nxt[j];
    }
}

int kmp(const char (&t)[M<<1]) {
    int ans = 0;
    int i = 0, j = 0;
    while (i<tLen) {
        if (j==-1 || t[i] == p[j]) {
            ++i; ++j;
        } else {
            j = nxt[j];
        }
        if (j == pLen) {
            ++ ans;
            j = nxt[j];
        }
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    f[0] = f[1] = 1; for (short i=2; i<T; ++i) f[i] = f[i-1] + f[i-2];
    int kase = 0;
    while (cin >> n) {
        cin >> p;
        pLen = strlen(p);
        if (pLen == 1) {
            d[0] = p[0] == '0'; d[1] = p[0] != '0';
            for (short i=2; i<=n; ++i) d[i] = d[i-1] + d[i-2];
        } else {
            getNext();
            int k = lower_bound(f, f+T, pLen) - f;
            t[0] = '1'; t[1] = '0'; t[f[k]] = '\0';
            for (short i=3; i<=k; ++i) memcpy(t+f[i-1], t, f[i-2]);
            int d0 = -1, d1 = -1, d2 = -1;
            if (n > k) {
                memcpy(s, t+f[k]-pLen+1, pLen-1);
                memcpy(s+pLen-1, t, f[k-1]);
                s[tLen = pLen-1+f[k-1]] = '\0';
                d0 = kmp(s);
            }
            if (n > k+1) {
                if (f[k-1] < pLen -1) memcpy(s, t+f[k+1]-pLen+1, pLen-1-f[k-1]);
                memcpy(s+pLen-1-f[k-1], t, f[k-1]);
                memcpy(s+pLen-1, t, pLen-1);
                s[tLen = 2*pLen-2] = '\0';
                d1 = kmp(s);
            }
            if (n > k+2) {
                memcpy(s, t+f[k]-pLen+1, pLen-1);
                memcpy(s+pLen-1, t, pLen-1);
                s[tLen = 2*pLen-2] = '\0';
                d2 = kmp(s);
            }
            for (short i=0; i<=n; ++i) {
                if (i > k) {
                    d[i] = i==k+1 ? d[k] + d0 : (d[i-1] + d[i-2] + ((i&1) == (k&1) ? d1 : d2));
                } else if (i == k) {
                    tLen = f[k]; d[i] = kmp(t);
                } else d[i] = 0;
            }
        }
        cout << "Case " << ++kase << ": " << d[n] << endl;
    }
    return 0;
}