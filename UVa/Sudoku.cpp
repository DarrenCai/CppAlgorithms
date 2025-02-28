/**
 * UVa1309/LA2659
 * 数独
 * SEERC 2006
 */

#include <iostream>
#include <cstring>
using namespace std;

#define maxNode 17409   //16384+1025
#define maxC 1025
#define maxR 4096

short n=1024, sz, ansd, ans[maxR], S[maxC], H[maxR];
short row[maxNode], col[maxNode], L[maxNode], R[maxNode], U[maxNode], D[maxNode];

void init() {
    for (short i=0; i<=n; ++i) {
        S[i] = 0; U[i] = D[i] = i; L[i] = i-1; R[i] = i+1;
    }
    R[n] = 0; L[0] = n; sz = n+1;
    memset(H, 0, sizeof(H));
}

void link(short r, short c) {
    D[U[c]]=sz; U[sz]=U[c]; D[sz]=c; U[c]=sz;
    if(!H[r]) H[r]=L[sz]=R[sz]=sz;
    else {
        L[sz]=L[H[r]]; R[L[H[r]]]=sz;
        R[sz]=H[r]; L[H[r]]=sz;
    }
    row[sz] = r; col[sz]=c; ++ sz; ++ S[c];
}

void remove(short c) {
    L[R[c]] = L[c]; R[L[c]] = R[c];
    for (short i=D[c]; i!=c; i=D[i])
        for (short j=R[i]; j!=i; j=R[j]) {
            U[D[j]] = U[j]; D[U[j]] = D[j]; --S[col[j]];
        }
}

void restore(short c) {
    for (short i=U[c]; i!=c; i=U[i])
        for(short j=L[i]; j!=i; j=L[j]) {
            U[D[j]] = D[U[j]] = j; ++S[col[j]];
        }
    L[R[c]] = c; R[L[c]] = c;
}

bool dfs(short d=0) {
    if (!R[0]) {
        ansd = d;
        return true;
    }
    short c = R[0];
    for (short i=R[0]; i!=0; i=R[i])
        if (S[i] < S[c]) c = i;
    remove(c);
    for (short i=D[c]; i!=c; i=D[i]) {
        ans[d] = row[i];
        for (short j=R[i]; j!=i; j=R[j]) remove(col[j]);
        if (dfs(d+1)) return true;
        for (short j=L[i]; j!=i; j=L[j]) restore(col[j]);
    }
    restore(c);
    return false;
}

short encode(short a, short b, short c) {
    return a<<8 | b<<4 | c;
}

void decode(short code, short& a, short& b, short& c) {
    a = code; c = a&15; a>>=4; b = a&15; a>>=4;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    char sudoku[16][17]; int k=0;
    while (!cin.eof()) {
        for (short i=0; i<16; ++i) cin >> sudoku[i];
        if (k++) cout << endl;
        init();
        for (short r=0; r<16; ++r)
            for (short c=0; c<16; ++c)
                for (short v=0; v<16; ++v)
                    if (sudoku[r][c] == '-' || sudoku[r][c] == 'A'+v) {
                        short row = encode(r, c, v);
                        link(row, 1+encode(0, r, c));
                        link(row, 1+encode(1, r, v));
                        link(row, 1+encode(2, c, v));
                        link(row, 1+encode(3, ((r>>2)<<2)+(c>>2), v));
                    }
        dfs();
        for (short i=0; i<ansd; ++i) {
            short r, c, v; decode(ans[i], r, c, v);
            sudoku[r][c] = 'A'+v;
        }
        for (short i=0; i<16; ++i)
            cout << sudoku[i] << endl;
    }
    return 0;
}