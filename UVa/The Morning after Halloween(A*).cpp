/**
 * UVa1601
 * 万圣节后的早晨
 */

#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

#define abs(x) (x>0 ? x : -(x))

short w, h, n, a[3][2], b[3][2], c[3][2]; char s[16][16]; vector<char> m[16][16];
char d[5][2]={{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
map<int, short> g, hh; int t, goal;
struct cmp {
    bool operator() (int a, int b) const {
        return g[a]+hh[a] < g[b]+hh[b] || (g[a]+hh[a] == g[b]+hh[b] && a<b);
    }
};
set<int> close; set<int, cmp> open;

int convert(const short (&r)[3][2]) {
    int k = 0;
    for(char i=0; i<n; ++i)
        k = k*w*h + w*r[i][0] + r[i][1];
    return k;
}

void convert() {
    int tt = t; char i = n;
    while (i) {
        short p = tt % (w*h);
        a[--i][0] = p / w;
        a[i][1] = p % w;
        c[i][0] = a[i][0];
        c[i][1] = a[i][1];
        tt /= w*h;
    }   
}

short diff() {
    short ds, max=0;
    for (char i=0; i<n; ++i) {
        ds = abs(a[i][0]-c[i][0]) + abs(a[i][1]-c[i][1]);
        if (ds>max) max = ds;
    }
    return max;
}

bool expand() {
    int next = convert(c);
    if (!close.count(next)) {
        if (!open.count(next)) {
            g[next] = g[t] + 1;
            if (next == goal)
                return false;
            if (!hh.count(next))
                hh[next] = diff();
            open.insert(next);
        } else if (g[t]+1<g[next]) {
            g[next] = g[t]+1;
            open.erase(next);
            open.insert(next);
        }
    }
    return true;
}

void AStar() {
    while (!open.empty()) {
        t = *open.begin(); open.erase(open.begin()); convert();
        if (n==1)
            for (char i=m[a[0][0]][a[0][1]].size()-1; i>0; --i) {
                c[0][0] = a[0][0] + d[m[a[0][0]][a[0][1]][i]][0]; 
                c[0][1] = a[0][1] + d[m[a[0][0]][a[0][1]][i]][1];
                if (!expand()) return;
            }
        else if (n==2)
            for (char i=m[a[0][0]][a[0][1]].size()-1; i>=0; --i) {
                c[0][0] = a[0][0] + d[m[a[0][0]][a[0][1]][i]][0]; 
                c[0][1] = a[0][1] + d[m[a[0][0]][a[0][1]][i]][1];
                for (char j=m[a[1][0]][a[1][1]].size()-1; j>=0; --j) {
                    c[1][0] = a[1][0] + d[m[a[1][0]][a[1][1]][j]][0];
                    c[1][1] = a[1][1] + d[m[a[1][0]][a[1][1]][j]][1];
                    if ((c[0][0]==a[0][0] && c[0][1]==a[0][1] && c[1][0]==a[1][0] && c[1][1]==a[1][1]) ||
                        (c[0][0]==a[1][0] && c[0][1]==a[1][1] && c[1][0]==a[0][0] && c[1][1]==a[0][1]) ||
                        (c[0][0]==c[1][0] && c[0][1]==c[1][1])) continue;
                    if (!expand()) return;
                }
            }
        else for (char i=m[a[0][0]][a[0][1]].size()-1; i>=0; --i) {
                c[0][0] = a[0][0] + d[m[a[0][0]][a[0][1]][i]][0]; 
                c[0][1] = a[0][1] + d[m[a[0][0]][a[0][1]][i]][1];
                for (char j=m[a[1][0]][a[1][1]].size()-1; j>=0; --j) {
                    c[1][0] = a[1][0] + d[m[a[1][0]][a[1][1]][j]][0];
                    c[1][1] = a[1][1] + d[m[a[1][0]][a[1][1]][j]][1];
                    for (char k=m[a[2][0]][a[2][1]].size()-1; k>=0; --k) {
                        c[2][0] = a[2][0] + d[m[a[2][0]][a[2][1]][k]][0];
                        c[2][1] = a[2][1] + d[m[a[2][0]][a[2][1]][k]][1];
                        if ((c[0][0]==a[1][0] && c[0][1]==a[1][1] && c[1][0]==a[0][0] && c[1][1]==a[0][1]) ||
                            (c[0][0]==a[2][0] && c[0][1]==a[2][1] && c[2][0]==a[0][0] && c[2][1]==a[0][1]) ||
                            (c[1][0]==a[2][0] && c[1][1]==a[2][1] && c[2][0]==a[1][0] && c[2][1]==a[1][1]) ||
                            (c[0][0]==a[0][0] && c[0][1]==a[0][1] && c[1][0]==a[1][0] && c[1][1]==a[1][1] &&
                            c[2][0]==a[2][0] && c[2][1]==a[2][1]) || (c[0][0]==c[1][0] && c[0][1]==c[1][1]) ||
                            (c[0][0]==c[2][0] && c[0][1]==c[2][1]) || (c[1][0]==c[2][0] && c[1][1]==c[2][1])) continue;
                        if (!expand()) return;
                    }
                }
            }
        close.insert(t);
    }
}

int main()
{
    while (cin >> w >> h >> n && w) {
        for (char i = 0; i < h; ++i) {
            cin.get();
            for (char j = 0; j < w; ++j) {
                s[i][j] = cin.get();
                if (s[i][j] >= 'a' && s[i][j] < 'd') {
                    a[s[i][j] - 'a'][0] = i;
                    a[s[i][j] - 'a'][1] = j;
                } else if (s[i][j] >= 'A' && s[i][j] < 'D') {
                    b[s[i][j] - 'A'][0] = i;
                    b[s[i][j] - 'A'][1] = j;
                }
            }
        }
        for (char i = 0; i < h; ++i)
            for (char j = 0; j < w; ++j)
                if (s[i][j] != '#') {
                    m[i][j].clear(); m[i][j].push_back(0);
                    if (i && s[i-1][j]!='#') m[i][j].push_back(1);
                    if (i<h-1 && s[i+1][j]!='#') m[i][j].push_back(2);
                    if (j && s[i][j-1]!='#') m[i][j].push_back(3);
                    if (j<w-1 && s[i][j+1]!='#') m[i][j].push_back(4);
                }
        t = convert(a);
        goal = convert(b);
        if (t == goal) {
            cout << 0 << endl;
        } else {
            open.insert(t);
            g[t] = 0;
            AStar();
            cout << g[goal] << endl;
            open.clear();
            close.clear();
            hh.clear();
        }
    }
    return 0;
}