/**
 * UVa 1103
 * 古代象形符号
 */

#include <iostream>
#include <map>

void visit(bool s[200][200], int mark[200][200], int m, int n, int i, int j, const int t) {
    if(i-1>=0 && s[i-1][j] && !mark[i-1][j])    { mark[i-1][j] = t; visit(s, mark, m, n, i-1, j, t); }
    if(i+1<m && s[i+1][j] && !mark[i+1][j])     { mark[i+1][j] = t; visit(s, mark, m, n, i+1, j, t); }
    if(j-1>=0 && s[i][j-1] && !mark[i][j-1])    { mark[i][j-1] = t; visit(s, mark, m, n, i, j-1, t); }
    if(j+1<n && s[i][j+1] && !mark[i][j+1])     { mark[i][j+1] = t; visit(s, mark, m, n, i, j+1, t); }
}

void visit1(bool s[200][200], int mark[200][200], int m, int n, int i, int j, int& f, int& r) {
    if(i==0 || i==m-1 || j==0 || j==n-1)    r = 0;
    if(i-1 >= 0) {
        if(!s[i-1][j] && !mark[i-1][j])    { mark[i-1][j] = 1; visit1(s, mark, m, n, i-1, j, f, r); }
        if(s[i-1][j] && r)   { if(!f)    f=mark[i-1][j];   else if(f!=mark[i-1][j])    r=0;}
    }
    if(i+1 < m ) {
        if(!s[i+1][j] && !mark[i+1][j])    { mark[i+1][j] = 1; visit1(s, mark, m, n, i+1, j, f, r); }
        if(s[i+1][j] && r)   { if(!f)    f=mark[i+1][j];   else if(f!=mark[i+1][j])    r=0;}
    }
    if(j-1 >= 0) {
        if(!s[i][j-1] && !mark[i][j-1])    { mark[i][j-1] = 1; visit1(s, mark, m, n, i, j-1, f, r); }
        if(s[i][j-1] && r)   { if(!f)    f=mark[i][j-1];   else if(f!=mark[i][j-1])    r=0;}
    }
    if(j+1 < n) {
        if(!s[i][j+1] && !mark[i][j+1])    { mark[i][j+1] = 1; visit1(s, mark, m, n, i, j+1, f, r); }
        if(s[i][j+1] && r)   { if(!f)    f=mark[i][j+1];   else if(f!=mark[i][j+1])    r=0;}
    }
}

int main()
{
    using namespace std;
    const char glyph[6] = {'W', 'A', 'K', 'J', 'S', 'D'}; int m, n, k=0;
    while(cin >> m >> n && m && n) {
        bool s[200][200] = {false}; int mark[200][200] = {0};
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                int t = j<<2; char c; cin >> c;
                switch(c) {
                    case '1': s[i][t+3] = true; break;
                    case '2': s[i][t+2] = true; break;
                    case '3': s[i][t+2] = true; s[i][t+3] = true; break;
                    case '4': s[i][t+1] = true; break;
                    case '5': s[i][t+1] = true; s[i][t+3] = true; break;
                    case '6': s[i][t+1] = true; s[i][t+2] = true; break;
                    case '7': s[i][t+1] = true; s[i][t+2] = true; s[i][t+3] = true; break;
                    case '8': s[i][t] = true; break;
                    case '9': s[i][t] = true; s[i][t+3] = true; break;
                    case 'a': s[i][t] = true; s[i][t+2] = true; break;
                    case 'b': s[i][t] = true; s[i][t+2] = true; s[i][t+3] = true; break;
                    case 'c': s[i][t] = true; s[i][t+1] = true; break;
                    case 'd': s[i][t] = true; s[i][t+1] = true; s[i][t+3] = true; break;
                    case 'e': s[i][t] = true; s[i][t+1] = true; s[i][t+2] = true; break;
                    case 'f': s[i][t] = true; s[i][t+1] = true; s[i][t+2] = true; s[i][t+3] = true; break;
                }
            }
        }
        map<int, int> sum; int t=0, recg[6]={0}; n <<= 2;
        for(int i=0; i<m; ++i)
            for(int j=0; j<n; ++j)
                if(s[i][j] && !mark[i][j])    { mark[i][j] = ++t; sum[t] = 0; visit(s, mark, m, n, i, j, t); }
        for(int i=0; i<m; ++i)
            for(int j=0; j<n; ++j)
                if(!s[i][j] && !mark[i][j]) { mark[i][j] = 1; int f=0, r=1; visit1(s, mark, m, n, i, j, f, r); if(r)   ++sum[f];}
        for(int i=1; i<=t; ++i) { ++recg[sum[i]]; }
        cout << "Case " << ++k << ": ";
        if(recg[1]) for(int i=0; i<recg[1]; ++i) cout << 'A';
        if(recg[5]) for(int i=0; i<recg[5]; ++i) cout << 'D';
        if(recg[3]) for(int i=0; i<recg[3]; ++i) cout << 'J';
        if(recg[2]) for(int i=0; i<recg[2]; ++i) cout << 'K';
        if(recg[4]) for(int i=0; i<recg[4]; ++i) cout << 'S';
        if(recg[0]) for(int i=0; i<recg[0]; ++i) cout << 'W';
        cout << endl;
    }
    return 0;
}