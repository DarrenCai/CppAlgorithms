#include <cstring>
using namespace std;

#define maxNode 100000
#define maxC 1000
#define maxR 1000

int n, sz, ans;
int L[maxNode], R[maxNode], U[maxNode], D[maxNode], col[maxNode], S[maxC], H[maxR];

void init() {
    for (int i=0; i<=n; ++i) {
        S[i] = 0; U[i] = D[i] = i; L[i] = i-1; R[i] = i+1;
    }
    R[n] = 0; L[0] = n; sz = n+1; ans = n;
    memset(H, 0, sizeof(H));
}

void link(int r, int c) {
    D[U[c]]=sz; U[sz]=U[c]; D[sz]=c; U[c]=sz;
    if(!H[r]) H[r]=L[sz]=R[sz]=sz;
    else {
        L[sz]=L[H[r]]; R[L[H[r]]]=sz;
        R[sz]=H[r]; L[H[r]]=sz;
    }
    col[sz]=c; ++ sz; ++ S[c];
}

void remove(int c) {
    for(int i=D[c]; i!=c; i=D[i])
        L[R[i]] = L[i], R[L[i]] = R[i];
}

void restore(int c) {
    for(int i=U[c]; i!=c; i=U[i])
        L[R[i]] = R[L[i]] = i;
}

bool has[maxC];
int h() {       //用精确覆盖作为最优剪枝的评估函数
    int res=0;
    memset(has, false, sizeof(has));
    for(int i=R[0]; i!=0; i=R[i]) 
        if(!has[i]) {
            ++ res;
            for(int j=D[i]; j!=i; j=D[j])
                for(int k=R[j]; k!=j; k=R[k])
                    has[col[k]] = true;
        }
    return res;
}

void dfs(int d=0) {     //根据具体问题选择限制搜索深度或直接求解
    if (d+h() > ans) return;
    if (!R[0]) {
        if (d < ans) ans = d;
        return;
    }
    int c = R[0];
    for (int i=R[0]; i!=0; i=R[i])
        if (S[i] < S[c]) c = i;
    for(int i=D[c]; i!=c; i=D[i]) {
        remove(i);
        for(int j=R[i]; j!=i; j=R[j])
            remove(j);
        dfs(d+1);
        for(int j=L[i]; j!=i; j=L[j])
            restore(j);
        restore(i);
    }
}