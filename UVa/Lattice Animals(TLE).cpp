/**
 * UVa1602
 * 网格动物
 */

#include <iostream>
#include <cstring>
#include <set>
using namespace std;

struct Cell {
    char x, y;
    Cell(){}
    Cell(char x, char y):x(x),y(y){}
    bool operator< (const Cell& rhs) const {
        return x<rhs.x || (x==rhs.x && y<rhs.y);
    }
};
typedef set<Cell> Polyomino;

short n, w, h, c; char x, y, mp[10][10]; Cell num[100];
Polyomino s, ss; set<Polyomino> ls;

void normalize(const Polyomino& s) {
    char minX = 127, minY = 127; ss.clear();
    for (Polyomino::iterator it = s.begin(); it != s.end(); ++it) {
        if (it->x < minX) minX = it->x;
        if (it->y < minY) minY = it->y;
    }
    for (Polyomino::iterator it = s.begin(); it != s.end(); ++it)
        ss.insert(Cell(it->x-minX, it->y-minY));
}

void rotate90(Polyomino& s) {
    Polyomino:: iterator it = s.begin();
    Polyomino s1; s1.insert(*it);
    char ox = it->x, oy = it->y;
    while (++it != s.end())
        s1.insert(Cell(ox-it->y+oy, oy+it->x-ox));
    s=s1; normalize(s);
}

void flipVertical(Polyomino& s) {
    Polyomino:: iterator it = s.begin();
    Polyomino s1; s1.insert(*it);
    char oy = it->y;
    while (++it != s.end())
        s1.insert(Cell(it->x, (oy<<1)-it->y));
    s=s1; normalize(s);
}

void insert(Polyomino& s) {
    ls.insert(ss);
    rotate90(s); ls.insert(ss);
    rotate90(s); ls.insert(ss);
    rotate90(s); ls.insert(ss);
    flipVertical(s); ls.insert(ss);
    rotate90(s); ls.insert(ss);
    rotate90(s); ls.insert(ss);
    rotate90(s); ls.insert(ss);
    ++ c;
}

void search(char cur=0, char t=0) {
    char tt = t, pn[3];
    if ((num[cur].x==x && num[cur].y-1>y) || (num[cur].x>x && num[cur].y>=1)) {
        Cell p = Cell(num[cur].x, num[cur].y-1);
        if (!s.count(p) && mp[p.x][p.y]>tt+1) {
            pn[tt-t]=mp[p.x][p.y]; num[++tt]=p; mp[p.x][p.y]=tt;
        }
    }
    if ((num[cur].y==y && num[cur].x-1>x) || (num[cur].y>y && num[cur].x>=1)) {
        Cell p = Cell(num[cur].x-1, num[cur].y);
        if (!s.count(p) && mp[p.x][p.y]>tt+1) {
            pn[tt-t]=mp[p.x][p.y]; num[++tt]=p; mp[p.x][p.y]=tt;
        }
    }
    if (num[cur].x>=x && num[cur].y+1<h) {
        Cell p = Cell(num[cur].x, num[cur].y+1);
        if (!s.count(p) && mp[p.x][p.y]>tt+1) {
            pn[tt-t]=mp[p.x][p.y]; num[++tt]=p; mp[p.x][p.y]=tt;
        }
    }
    if (num[cur].y>=y && num[cur].x+1<w) {
        Cell p = Cell(num[cur].x+1, num[cur].y);
        if (!s.count(p) && mp[p.x][p.y]>tt+1) {
            pn[tt-t]=mp[p.x][p.y]; num[++tt]=p; mp[p.x][p.y]=tt;
        }
    }
    for (char i=cur+1; i<=tt; ++i) {
        s.insert(num[i]);
        if (s.size() == n) {
            Polyomino s1(s); normalize(s1);
            if (!ls.count(ss)) insert(s1);
        } else search(i, tt);
        s.erase(num[i]);
    }
    do {
        mp[num[tt].x][num[tt].y] = pn[tt-t-1];
    } while (--tt > t);
}

int main()
{
    memset(mp, 100, 100);
    while (cin >> n >> w >> h) {
        char wh = w*h;
        if (n>wh) {
            cout << 0 << endl;
        } else if (n==wh || n==1 || n==2) {
            cout << 1 << endl;
        } else {
            c = 0; bool ok = true;
            for (x=0; ok && x<w; ++x) {
                for (y=0; ok && y<h; ++y) {
                    if (x*h + y + n >= wh) ok = false;
                    num[0] = Cell(x, y);
                    s.insert(num[0]);
                    search();
                    s.clear();
                }
            }
            cout << c << endl;
            ls.clear();
        }
    }
    return 0;
}