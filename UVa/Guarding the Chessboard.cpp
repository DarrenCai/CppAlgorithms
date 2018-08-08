/**
 * UVa11214
 * 守卫棋盘
 */

#include <iostream>
#include <cstring>
using namespace std;

#define maxNode 4000
#define maxC 101
#define maxR 100

short n, sz, ans;
short L[maxNode], R[maxNode], U[maxNode], D[maxNode], col[maxNode], S[maxC], H[maxR];

void init() {
    for (short i=0; i<=n; ++i) {
        S[i] = 0; U[i] = D[i] = i; L[i] = i-1; R[i] = i+1;
    }
    R[n] = 0; L[0] = n; sz = n+1; ans = n;
    memset(H, 0, sizeof(H));
}

void link(short r, short c) {
    D[U[c]]=sz; U[sz]=U[c]; D[sz]=c; U[c]=sz;
    if(!H[r]) H[r]=L[sz]=R[sz]=sz;
    else {
        L[sz]=L[H[r]]; R[L[H[r]]]=sz;
        R[sz]=H[r]; L[H[r]]=sz;
    }
    col[sz]=c; ++ sz; ++ S[c];
}

void remove(short c) {
    for(short i=D[c]; i!=c; i=D[i])
        L[R[i]] = L[i], R[L[i]] = R[i];
}

void restore(short c) {
    for(short i=U[c]; i!=c; i=U[i])
        L[R[i]] = R[L[i]] = i;
}

bool has[maxC];
short h() {
    short res=0;
    memset(has, false, sizeof(has));
    for(short i=R[0]; i!=0; i=R[i]) 
        if(!has[i]) {
            ++ res;
            for(short j=D[i]; j!=i; j=D[j])
                for(short k=R[j]; k!=j; k=R[k])
                    has[col[k]] = true;
        }
    return res;
}

void dfs(short d=0) {
    if (d+h() >= ans) return;
    if (!R[0]) {
        if (d < ans) ans = d;
        return;
    }
    short c = R[0];
    for (short i=R[0]; i!=0; i=R[i])
        if (S[i] < S[c]) c = i;
    for(short i=D[c]; i!=c; i=D[i]) {
        remove(i);
        for(short j=R[i]; j!=i; j=R[j])
            remove(j), --S[col[j]];
        dfs(d+1);
        for(short j=L[i]; j!=i; j=L[j])
            restore(j), ++S[col[j]];
        restore(i);
    }
}

int main()
{
    short n, m, k=0;
    while (cin>>n>>m && n) {
        short num[100] = {0}; ::n=0;
        for (short i=0; i<n; ++i) for (short j=0; j<m; ++j) {
            char c; cin>>c; if (c=='X') num[i*m + j] = ++::n;
        }
        init();
        for (short i=0; i<n; ++i) for (short j=0; j<m; ++j) {
            short row = i*m + j, t; if (num[row]) link(row, num[row]);
            for (short r=0; r<n; ++r) { if (r==i) continue; t = r*m + j; if (num[t]) link(row, num[t]); }
            for (short c=0; c<m; ++c) { if (c==j) continue; t = i*m + c; if (num[t]) link(row, num[t]); }
            for (short k=min(short(n-1-i), j); k; --k) { t = (i+k)*m + j-k; if (num[t]) link(row, num[t]); }
            for (short k=min(i, short(n-1-j)); k; --k) { t = (i-k)*m + j+k; if (num[t]) link(row, num[t]); }
            for (short k=min(i, j); k; --k) { t = (i-k)*m + j-k; if (num[t]) link(row, num[t]); }
            for (short k=min(n-1-i, n-1-j); k; --k) { t = (i+k)*m + j+k; if (num[t]) link(row, num[t]); }
        }
        dfs();
        cout << "Case " << ++k << ": " << ans << endl;
    }
    return 0;
}