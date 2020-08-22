/**
 * UVa1204
 * 有趣的游戏
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 20
#define M 110
#define min(a, b) (a<b ? a:b)
short n, d[1<<N][N<<1], ans[1<<N][N<<1], c[N<<1][N<<1], l[N]; char s[N][M], t[N*M+1];

bool contains(short i, short j) {
    short n1 = l[i], n2 = l[j];
    if (n1 < n2) return false;
    for (short ss=n1-n2; ss>=0; --ss) {
        for (short t=n2-1, ii=0; s[i][ss+ii] == s[j][ii]; ++ii) if (ii==t) return true;
        for (short t=n2-1, ii=0; s[i][ss+ii] == s[j][t-ii]; ++ii) if (ii==t) return true;
    }
    return false;
}

void get(short i, short j) {
    c[i][j] = c[n+j][n+i] = c[i][n+j] = c[j][n+i] = c[n+i][j] = c[n+j][i] = c[n+i][n+j] = c[j][i] = 0;
    for (short ll=min(l[i],l[j]); ll>0; --ll) {
        if (!c[i][j]) {
            short ii=l[i]-ll, jj=0;
            while (jj<ll && s[j][jj] == s[i][ii+jj]) ++jj;
            if (jj == ll) c[i][j] = c[n+j][n+i] = ll;
        }
        if (!c[i][n+j]) {
            short ii=l[i]-ll, jj=0;
            while (jj<ll && s[j][l[j]-1-jj] == s[i][ii+jj]) ++jj;
            if (jj == ll) c[i][n+j] = c[j][n+i] = ll;
        }
        if (!c[n+i][j]) {
            short ii=ll-1, jj=0;
            while (jj<ll && s[j][jj] == s[i][ii-jj]) ++jj;
            if (jj == ll) c[n+i][j] = c[n+j][i] = ll;
        }
        if (!c[n+i][n+j]) {
            short ii=ll-1, jj=0;
            while (jj<ll && s[j][l[j]-1-jj] == s[i][ii-jj]) ++jj;
            if (jj == ll) c[n+i][n+j] = c[j][i] = ll;
        }
    }
}

void str(int ss, int i) {
    int ii = ans[ss][i], iii=i >= n ? i- n : i;
    if (ii > -1) {
        int s1 = ss ^ (1<<iii);
        str(s1, ii);
        if (i < n) for (short j=c[ii][i], jj=d[s1][ii]; j<l[iii]; ++j, ++jj) t[jj] = s[iii][j];
        else for (short j=l[iii]-c[ii][i]-1, jj=d[s1][ii]; j>=0; --j, ++jj) t[jj] = s[iii][j];
        t[d[ss][i]] = 0;
    } else {
        memcpy(t, s[i], sizeof(s[i]));
    }
}

short calc() {
    short len = strlen(t);
    for (short i=2, j; i<len; ++i) {
        for (j=i; j<len; ++j) if (t[j] != t[j%i]) break;
        if (j==len) return i;
    }
    return len;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) {
        for (short i=0; i<n; ++i) {
            cin >> s[i];
            short j=i; l[i] = strlen(s[i]);
            for (short k=0; k<j; ++k) if (contains(k, j)) { --j; --n; break; }
            if (j == i) {
                for (short k=0; k<j; ++k) if (contains(i, k)) memcpy(s[k], s[j-1], sizeof(s[k])), l[k]=l[j-1], --j, --k, --n;
                if (j<i) memcpy(s[j], s[i], sizeof(s[i])), l[j] = l[i];
            }
            i = j;
        }
        if (n > 1) {
            for (short i=0; i<n; ++i) for (short j=i+1; j<n; ++j) get(i, j);
            memset(d, -1, sizeof(d)); d[1][0] = l[0]; ans[1][0] = -1;
            for (int ss=1, m=(1<<n); ss<m; ++ss) for (int i=0; i<n; ++i) if ((ss & (1<<i))) {
                for (short j=1; j<n; ++j) if (!(ss & (1<<j))) {
                    int s1 = ss | (1<<j);
                    if (d[ss][i] > 0 && (d[s1][j] < 0 || d[ss][i]+l[j]-c[i][j] < d[s1][j])) d[s1][j] = d[ss][i]+l[j]-c[i][j], ans[s1][j] = i;
                    if (d[ss][i] > 0 && (d[s1][n+j] < 0 || d[ss][i]+l[j]-c[i][n+j] < d[s1][n+j])) d[s1][n+j] = d[ss][i]+l[j]-c[i][n+j], ans[s1][n+j] = i;
                    if (d[ss][n+i] > 0 && (d[s1][j] < 0 || d[ss][n+i]+l[j]-c[n+i][j] < d[s1][j])) d[s1][j] = d[ss][n+i]+l[j]-c[n+i][j], ans[s1][j] = n+i;
                    if (d[ss][n+i] > 0 && (d[s1][n+j] < 0 || d[ss][n+i]+l[j]-c[n+i][n+j] < d[s1][n+j])) d[s1][n+j] = d[ss][n+i]+l[j]-c[n+i][n+j], ans[s1][n+j] = n+i;
                }
            }
            int m = (1<<n)-1, mi = N*M;
            for (int i=1; i<n; ++i) {
                if (d[m][i] > 0) str(m, i), mi = min(mi, calc());
                if (d[m][n+i] > 0) str(m, n+i), mi = min(mi, calc());
            }
            cout << mi << endl;
        } else {
            memcpy(t, s[0], sizeof(s[0]));
            cout << calc() << endl;
        }
    }
    return 0;
}