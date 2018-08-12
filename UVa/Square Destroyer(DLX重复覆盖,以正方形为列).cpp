/**
 * UVa1603
 * 破坏正方形
 */

#include <iostream>
#include <cstring>
using namespace std;

#define maxNode 600
#define maxC 56
#define maxR 60

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
            remove(j);
        dfs(d+1);
        for(short j=L[i]; j!=i; j=L[j])
            restore(j);
        restore(i);
    }
}

int main()
{
    short t, N, k, e[maxR]; cin >> t;
    while (t--) {
        cin >> N >> k;
        n = N*(N+1)*(2*N+1)/6;
        memset(e, 1, sizeof(e));
        init();
        char offset = 1+(N<<1), s=0;
        for (short i=0; i<k; ++i) {
            short j; cin >> j; e[--j] = 0;
        }
        for (char l=1; l<=N; ++l)
            for (char x=N-l; x>=0; --x)
                for (char y=N-l; y>=0; --y) {
                    ++ s; bool ok = true;
                    for (char i=0; ok && i<l; ++i) 
                        if (!e[x*offset+y+i] || !e[(x+l)*offset+y+i] || 
                            !e[(x+i)*offset+N+y] || !e[(x+i)*offset+N+y+l]) ok = false;
                    if (ok) {
                        for (char i=0; ok && i<l; ++i) {
                            link(x*offset+y+i, s);
                            link((x+l)*offset+y+i, s);
                            link((x+i)*offset+N+y, s);
                            link((x+i)*offset+N+y+l, s);
                        }
                    } else {
                        R[L[s]]=R[s]; L[R[s]]=L[s];
                    }
                }
        dfs();
        cout << ans << endl;
    }
    return 0;
}