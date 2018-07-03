#include <cstring>
using namespace std;

#define maxNode 100000
#define maxC 1000
#define maxR 1000

//列编号为1～n,节点0是表头节点;节点1～n是各列顶部的虚拟节点
int n, sz;                                              //列数，节点总数
int S[maxC], H[maxR];                                   //各列节点数，各行头节点

int row[maxNode], col[maxNode];                         //各节点行列编号
int L[maxNode], R[maxNode], U[maxNode], D[maxNode];     //4方向循环链表

int ansd, ans[maxR];                                    //解

void init() {
    //虚拟节点
    for (int i=0; i<=n; ++i) {
        S[i] = 0; U[i] = D[i] = i; L[i] = i-1; R[i] = i+1;
    }
    R[n] = 0; L[0] = n; sz = n+1;
    memset(H, 0, sizeof(H));
}

void link(int r, int c) {
    D[U[c]]=sz; U[sz]=U[c]; D[sz]=c; U[c]=sz;
    if(!H[r]) H[r]=L[sz]=R[sz]=sz;
    else {
        L[sz]=L[H[r]]; R[L[H[r]]]=sz;
        R[sz]=H[r]; L[H[r]]=sz;
    }
    row[sz] = r; col[sz]=c; ++ sz; ++ S[c];
}

void remove(int c) {
    L[R[c]] = L[c]; R[L[c]] = R[c];
    for (int i=D[c]; i!=c; i=D[i])
        for (int j=R[i]; j!=i; j=R[j]) {
            U[D[j]] = U[j]; D[U[j]] = D[j]; --S[col[j]];
        }
}

void restore(int c) {
    for (int i=U[c]; i!=c; i=U[i])
        for(int j=L[i]; j!=i; j=L[j]) {
            U[D[j]] = D[U[j]] = j; ++S[col[j]];
        }
    L[R[c]] = c; R[L[c]] = c;
}

//d为递归深度,这个其实是具体的dance函数实现,一般是dfs
bool dfs(int d=0) {
    if (!R[0]) {                                    //找到解
        ansd = d;                                       //记录解的长度
        return true;
    }

    //找节点数最少的列c
    int c = R[0];                                       //第一个未删除的列
    for (int i=R[0]; i!=0; i=R[i])
        if (S[i] < S[c]) c = i;
    
    remove(c);                                          //删除第c列
    for (int i=D[c]; i!=c; i=D[i]) {
        ans[d] = row[i];
        for (int j=R[i]; j!=i; j=R[j]) remove(col[j]);  //删除节点i所在行能覆盖的所有其他列
        if (dfs(d+1)) return true;
        for (int j=L[i]; j!=i; j=L[j]) restore(col[j]); //恢复节点i所在行能覆盖的所有其他列
    }
    restore(c);                                         //恢复第c列

    return false;
}