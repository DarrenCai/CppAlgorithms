/**
 * UVa1601
 * 万圣节后的早晨
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <set>
using namespace std;

#define abs(x) (x>0 ? x : -(x))

short w, h, n, a[3], b[3], c[3]; char d[5]={0, -16, 16, -1, 1}, s[256]; vector<char> m[256];
map<int, short> g, hh; int t, goal;
struct cmp {
    bool operator() (int a, int b) const {
        return g[a]+hh[a] < g[b]+hh[b] || (g[a]+hh[a] == g[b]+hh[b] && a<b);
    }
};
set<int> close; set<int, cmp> open;

int convert(const short (&r)[3]) {
    return r[0]<<16 | r[1]<<8 | r[2];
}

void convert() {
    int tt = t; char i = 3;
    while (i) {
        a[--i] = tt & 0xff;
        c[i] = a[i];
        tt >>= 8;
    }
}

short diff() {
    short ds, max=0;
    for (char i=0; i<n; ++i) {
        ds = abs((a[i]>>4)-(c[i]>>4)) + abs((a[i]&0xf)-(c[i]%w&0xf));
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
            for (char i=m[a[0]].size()-1; i>0; --i) {
                c[0] = a[0] + d[m[a[0]][i]];
                if (!expand()) return;
            }
        else if (n==2)
            for (char i=m[a[0]].size()-1; i>=0; --i) {
                char dir = m[a[0]][i];
                c[0] = a[0] + d[m[a[0]][i]];
                for (char j=m[a[1]].size()-1; j>=0; --j) {
                    dir = m[a[1]][j];
                    c[1] = a[1] + d[m[a[1]][j]];
                    if ((c[0]==a[0] && c[1]==a[1]) || (c[0]==a[1] && c[1]==a[0]) || c[0]==c[1]) continue;
                    if (!expand()) return;
                }
            }
        else for (char i=m[a[0]].size()-1; i>=0; --i) {
                c[0] = a[0] + d[m[a[0]][i]]; 
                for (char j=m[a[1]].size()-1; j>=0; --j) {
                    c[1] = a[1] + d[m[a[1]][j]];
                    for (char k=m[a[2]].size()-1; k>=0; --k) {
                        c[2] = a[2] + d[m[a[2]][k]];
                        if ((c[0]==a[1] && c[1]==a[0]) || (c[0]==a[2] && c[2]==a[0]) ||
                            (c[1]==a[2] && c[2]==a[1]) || (c[0]==a[0] && c[1]==a[1] && c[2]==a[2]) ||
                            c[0]==c[1] || c[0]==c[2] || c[1]==c[2]) continue;
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
        memset(s, '#', 256);
        for (char i = 0; i < h; ++i) {
            cin.get();
            for (char j = 0; j < w; ++j) {
                short k = i<<4 | j;
                s[k] = cin.get();
                if (s[k] >= 'a' && s[k] < 'd') {
                    a[s[k] - 'a'] = k;
                } else if (s[k] >= 'A' && s[k] < 'D') {
                    b[s[k] - 'A'] = k;
                }
            }
        }
        for (short i=0; i<256; ++i)
            if (s[i] != '#') {
                m[i].clear(); m[i].push_back(0);
                if (i>=16 && s[i-16]!='#') m[i].push_back(1);
                if (i<240 && s[i+16]!='#') m[i].push_back(2);
                if (i && s[i-1]!='#') m[i].push_back(3);
                if (i<255 && s[i+1]!='#') m[i].push_back(4);
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