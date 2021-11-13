/**
 * UVa1663
 * 净化器
 */

#include <iostream>
#include <cstring>
#include <string>
#include <map>
using namespace std;

#define maxNode 100000
#define maxC 50000
#define maxR 5200

int n, m, sz, ans, g[maxR/5][10], c[maxR/5];
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
int h() {
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

void dfs(int d=0) {
    if (d+h() >= ans) return;
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

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m && n) {
        map<string, short> id;
        for (int i=1; i<=m; ++i) {
            string s; cin >> s; int f = -1;
            for (int j=0; j<n; ++j) if (s[j]=='*') {
                f = j; break;
            }
            if (f >= 0) {
                s[f] = '0';
                if (!id.count(s)) id[s] = id.size();
                s[f] = '1';
                if (!id.count(s)) id[s] = id.size();
            } else if (!id.count(s)) id[s] = id.size();
        }
        memset(c, m=0, sizeof(c));
        for (map<string, short>::iterator it = id.begin(); it != id.end(); ++it) {
            const string& a = it->first; int x = it->second;
            for (map<string, short>::iterator it1 = it; ++it1 != id.end();) {
                const string& b = it1->first; int d = 0, y = it1->second;
                for (int i=0; i<n; ++i) if (a[i]!=b[i] && ++d>1) break;
                if (d==1) g[x][c[x]++] = m, g[y][c[y]++] = m++;
            }
        }
        n = 0;
        for (int i=id.size()-1; i>=0; --i) for (short j=0; j<c[i]; ++j) for (short k=j+1; k<c[i]; ++k) ++n;
        init(); n = 0;
        for (int i=id.size()-1; i>=0; --i) for (short j=0; j<c[i]; ++j) for (short k=j+1; k<c[i]; ++k) {
            link(g[i][j], ++n); link(g[i][k], n);
        }
        dfs();
        cout << id.size()+ans-m << endl;
    }
    return 0;
}