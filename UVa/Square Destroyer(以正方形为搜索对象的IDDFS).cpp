/**
 * UVa1603
 * 破坏正方形
 */

#include <iostream>
#include <cstring>
using namespace std;

short n, k, depth; char e[60], size[5][5][6], maxMatch, offset;

void takeH(char x, char y, char l) {
    for (char ll=l; ll<=x; ++ll) {
        char xx = x-ll;
        for (short i = max(y+1-ll, 0); i<=y && i<=n-ll; ++i)
            -- size[xx][i][ll];
    }
    for (char ll=l; ll<=n-x; ++ll)
        for (short i = max(y+1-ll, 0); i<=y && i<=n-ll; ++i)
            -- size[x][i][ll];
}

void putH(char x, char y, char l) {
    for (char ll=l; ll<=x; ++ll) {
        char xx = x-ll;
        for (short i = max(y+1-ll, 0); i<=y && i<=n-ll; ++i)
            ++ size[xx][i][ll];
    }
    for (char ll=l; ll<=n-x; ++ll)
        for (short i = max(y+1-ll, 0); i<=y && i<=n-ll; ++i)
            ++ size[x][i][ll];
}

void takeV(char x, char y, char l) {
    for (char ll=l; ll<=y; ++ll) {
        char yy = y - ll;
        for (char i = max(x+1-ll, 0); i<=x && i<=n-ll; ++i)
            -- size[i][yy][ll];
    }
    for (char ll=l; ll<=n-y; ++ll)
        for (short i = max(x+1-ll, 0); i<=x && i<=n-ll; ++i)
            -- size[i][y][ll];
}

void putV(char x, char y, char l) {
    for (char ll=l; ll<=y; ++ll) {
        char yy = y - ll;
        for (char i = max(x+1-ll, 0); i<=x && i<=n-ll; ++i)
            ++ size[i][yy][ll];
    }
    for (char ll=l; ll<=n-y; ++ll)
        for (short i = max(x+1-ll, 0); i<=x && i<=n-ll; ++i)
            ++ size[i][y][ll];
}

bool IDDFS(char x=0, char y=0, char l=1, char step = 0) {
    if (y+l > n) { y = 0; ++x; }
    if (x+l > n) { x = 0; ++l; }
    if (l > n) return true;
    if (size[x][y][l] < l<<2) {
        return IDDFS(x, y+1, l, step);
    } else {
        for (char i=0; i<l; ++i) {
            char e1 = x*offset+y+i, e2 = (x+l)*offset+y+i,
                 e3 = (x+i)*offset+n+y, e4 = (x+i)*offset+n+y+l;
            if (e[e1]) {
                e[e1] = 0; takeH(x, y+i, l);
                if (step+1 <= depth && IDDFS(x, y+1, l, step+1)) return true;
                e[e1] = 1; putH(x, y+i, l);
            }
            if (e[e2]) {
                e[e2] = 0; takeH(x+l, y+i, l);
                if (step+1 <= depth && IDDFS(x, y+1, l, step+1)) return true;
                e[e2] = 1; putH(x+l, y+i, l);
            }
            if (e[e3]) {
                e[e3] = 0; takeV(x+i, y, l);
                if (step+1 <= depth && IDDFS(x, y+1, l, step+1)) return true;
                e[e3] = 1; putV(x+i, y, l);
            }
            if (e[e4]) {
                e[e4] = 0; takeV(x+i, y+l, l);
                if (step+1 <= depth && IDDFS(x, y+1, l, step+1)) return true;
                e[e4] = 1; putV(x+i, y+l, l);
            }
        }
    }
    return false;
}

int main()
{
    int t; cin >> t;
    while (t--) {
        cin >> n >> k;
        maxMatch = n*(n+1)<<1;
        offset = 1+(n<<1);
        memset(e, 1, maxMatch);
        for (short i=0; i<k; ++i) {
            short j; cin >> j; --j; e[j] = 0;
        }
        for (char l=1; l<=n; ++l)
            for (char x=n-l; x>=0; --x)
                for (char y=n-l; y>=0; --y) {
                    size[x][y][l] = 0;
                    for (char i=0; i<l; ++i) 
                        size[x][y][l] += 
                            e[x*offset+y+i] + e[(x+l)*offset+y+i] + e[(x+i)*offset+n+y] + e[(x+i)*offset+n+y+l];
                }
        for (depth=0; !IDDFS(); ++depth);
        cout << depth << endl;
    }
    return 0;
}