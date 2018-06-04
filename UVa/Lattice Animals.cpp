/**
 * UVa1602
 * 网格动物
 */

#include <iostream>
#include <set>
using namespace std;

struct Cell {
    char x, y;
    Cell(char x, char y):x(x),y(y){}
    bool operator< (const Cell& rhs) const {
        return x<rhs.x || (x==rhs.x && y<rhs.y);
    }
};
typedef set<Cell> Polyomino;

short c[11][11][11]={0}; set<Polyomino> poly[11];

Polyomino normalize(const Polyomino& s) {
    char minX = 127, minY = 127; Polyomino s1;
    for (Polyomino::iterator it = s.begin(); it != s.end(); ++it) {
        if (it->x < minX) minX = it->x;
        if (it->y < minY) minY = it->y;
    }
    for (Polyomino::iterator it = s.begin(); it != s.end(); ++it)
        s1.insert(Cell(it->x-minX, it->y-minY));
    return s1;
}

void rotate(Polyomino& s) {
    Polyomino:: iterator it = s.begin();
    Polyomino s1; s1.insert(*it);
    char ox = it->x, oy = it->y;
    while (++it != s.end())
        s1.insert(Cell(ox-it->y+oy, oy+it->x-ox));
    s = normalize(s1);
}

void flip(Polyomino& s) {       // flipVertical
    Polyomino:: iterator it = s.begin();
    Polyomino s1; s1.insert(*it);
    char oy = it->y;
    while (++it != s.end())
        s1.insert(Cell(it->x, (oy<<1)-it->y));
    s = normalize(s1);
}

void check(set<Polyomino>::const_iterator& it, char x, char y, set<Polyomino>& out) {
    Cell cell(x, y); if (it->count(cell)) return;
    Polyomino s(*it); s.insert(cell); s=normalize(s);
    if (out.count(s)) return;
    for (char i=0; i<3; ++i) {
        rotate(s); if (out.count(s)) return;
    }
    flip(s); if(out.count(s)) return;
    for (char i=0; i<3; ++i) {
        rotate(s); if (out.count(s)) return;
    }
    out.insert(s);
}

void generate() {
    Polyomino s; s.insert(Cell(0, 0)); poly[1].insert(s);
    for (char n=2; n<=10; ++n)
        for (set<Polyomino>::const_iterator it = poly[n-1].cbegin(); it != poly[n-1].cend(); ++it) 
            for (Polyomino::iterator it1 = it->begin(); it1 != it->end(); ++it1) {
                check(it, it1->x, it1->y-1, poly[n]);
                check(it, it1->x-1, it1->y, poly[n]);
                check(it, it1->x, it1->y+1, poly[n]);
                check(it, it1->x+1, it1->y, poly[n]);
            }
    for (char n=1; n<=10; ++n) 
        for (set<Polyomino>::iterator it = poly[n].begin(); it != poly[n].end(); ++it) {
            char maxX = 0, maxY = 0;
            for (Polyomino::iterator it1 = it->begin(); it1 != it->end(); ++it1) {
                if (it1->x > maxX) maxX = it1->x;
                if (it1->y > maxY) maxY = it1->y;
            }
            char mini = min(maxX, maxY), maxi = max(maxX, maxY);
            for (char w=1; w<=10; ++w) 
                for (char h=1; h<=10; ++h)
                    if (mini<min(w,h) && maxi<max(w,h)) ++ c[w][h][n];
        }
}

int main()
{
    generate();
    short n, w, h;
    while (cin >> n >> w >> h)
        cout << c[w][h][n] << endl;
    return 0;
}