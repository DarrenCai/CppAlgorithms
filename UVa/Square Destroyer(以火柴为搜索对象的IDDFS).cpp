/**
 * UVa1603/LA2328
 * 破坏正方形
 * Taejon 2001
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

short n, k, depth; char e[60], d[60], size[5][5][6], maxMatch, offset;
bool cmp(char a, char b) {return d[a] < d[b];}

void take(char x, char y, char l, char& cnt) {
    if (size[x][y][l] == l<<2) {
        -- cnt;
        for (char i=0; i<l; ++i) {
            char e1 = x*offset+y+i, e2 = (x+l)*offset+y+i,
                 e3 = (x+i)*offset+n+y, e4 = (x+i)*offset+n+y+l;
            -- d[e1]; --d[e2]; --d[e3]; --d[e4];
        }
    }
}

void put(char x, char y, char l, char& cnt) {
    if (size[x][y][l] == l<<2) {
        ++ cnt;
        for (char i=0; i<l; ++i) {
            char e1 = x*offset+y+i, e2 = (x+l)*offset+y+i,
                 e3 = (x+i)*offset+n+y, e4 = (x+i)*offset+n+y+l;
            ++ d[e1]; ++d[e2]; ++d[e3]; ++d[e4];
        }
    }
}

bool IDDFS(char cnt, vector<char> s, char step = 0) {
    if (cnt == 0) return true;
    for (char p = s.size()-1; p>=0; --p) {
        char edge = s[p], t = 1, sum = d[edge];
        while (t<=p && sum<cnt) sum += d[s[p-t++]];
        if (step+t > depth || sum<cnt) return false;
        vector<char> ss(s.begin(), s.begin()+p);
        char x = edge/(2*n+1), y = edge%(2*n+1);
        if (y < n) {
            for (char l=1; l<=x; ++l) {
                char i = x-l;
                for (short j = max(y+1-l, 0); j<=y && j<=n-l; ++j)
                    take(i, j, l, cnt), -- size[i][j][l];
            }
            for (char l=1; l<=n-x; ++l)
                for (char j = max(y+1-l, 0); j<=y && j<=n-l; ++j)
                    take(x, j, l, cnt), -- size[x][j][l];
            if (cnt == 0) return true;
            sort(ss.begin(), ss.end(), cmp);
            if (step+1 < depth && IDDFS(cnt, ss, step+1)) return true;
            for (char l=1; l<=x; ++l) {
                char i = x-l;
                for (short j = max(y+1-l, 0); j<=y && j<=n-l; ++j)
                    ++ size[i][j][l], put(i, j, l, cnt);
            }
            for (char l=1; l<=n-x; ++l)
                for (char j = max(y+1-l, 0); j<=y && j<=n-l; ++j)
                    ++ size[x][j][l], put(x, j, l, cnt);
        } else {
            y -= n;
            for (char l=1; l<=y; ++l) {
                char j = y - l;
                for (char i = max(x+1-l, 0); i<=x && i<=n-l; ++i)
                    take(i, j, l, cnt), -- size[i][j][l];
            }
            for (char l=1; l<=n-y; ++l)
                for (char i = max(x+1-l, 0); i<=x && i<=n-l; ++i)
                    take(i, y, l, cnt), -- size[i][y][l];
            if (cnt == 0) return true;
            sort(ss.begin(), ss.end(), cmp);
            if (step+1 < depth && IDDFS(cnt, ss, step+1)) return true;
            for (char l=1; l<=y; ++l) {
                char j = y - l;
                for (char i = max(x+1-l, 0); i<=x && i<=n-l; ++i)
                    ++ size[i][j][l], put(i, j, l, cnt);
            }
            for (char l=1; l<=n-y; ++l)
                for (char i = max(x+1-l, 0); i<=x && i<=n-l; ++i)
                    ++ size[i][y][l], put(i, y, l, cnt);
        }
    }
    return false;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        cin >> n >> k; char cnt = 0;
        maxMatch = n*(n+1)<<1;
        offset = 1+(n<<1);
        memset(e, 1, maxMatch);
        memset(d, 0, maxMatch);
        for (char i=0; i<k; ++i) {
            short j; cin >> j; --j; e[j] = 0;
        }
        for (char l=1; l<=n; ++l)
            for (char x=n-l; x>=0; --x)
                for (char y=n-l; y>=0; --y) {
                    size[x][y][l] = 0;
                    for (char i=0; i<l; ++i)
                        size[x][y][l] += 
                            e[x*offset+y+i] + e[(x+l)*offset+y+i] + e[(x+i)*offset+n+y] + e[(x+i)*offset+n+y+l];
                    put(x, y, l, cnt);
                }
        vector<char> s;
        for (char i=0; i<maxMatch; ++i) if (d[i]) s.push_back(i);
        sort(s.begin(), s.end(), cmp);
        for (depth=0; !IDDFS(cnt, s); ++depth);
        cout << depth << endl;
    }
    return 0;
}