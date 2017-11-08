/**
 * UVa810
 * 骰子难题
 *                 ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
 *                 |     ● |
 *                 |   ●   |
 *                 | ●     |
 * ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
 * |       |     ● | ●   ● | ●   ● |
 * |   ●   |       | ●   ● |   ●   |
 * |       | ●     | ●   ● | ●   ● |
 * ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
 *                 | ●   ● |
 *                 |       |
 *                 | ●   ● |
 *                 ⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯
 */

#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

char left(char face, char top) {
    if (face==1) {
        if (top==2) return 4;
        if (top==3) return 2;
        if (top==4) return 5;
        if (top==5) return 3;
    }
    if (top==1) return 7-left(top, face);
    if (face==2) {
        if (top==3) return 6;
        if (top==4) return 1;
        if (top==6) return 4;
    }
    if (top==2) return 7-left(top, face);
    if (face>3 && top>3) return left(7-face, 7-top);
    if (face>3) return 7-left(7-face, top);
    return 7-left(face, 7-top);
}

short m, n, r0, c0, t0, f0; char maze[11][11]; set<unsigned short> visit;
bool search(char r, char c, char f, char t, vector<unsigned char>& sln, set<unsigned short>& s) {
    unsigned char v = r<<4 | c; unsigned short k = (v<<8) + (f<<4 | t);
    if (sln.size() > 0 && sln[0] == v) {
        sln.push_back(v); s.insert(k);
        return true;
    }
    if (s.count(k) || visit.count(k)) return false;
    sln.push_back(v); s.insert(k);
    if (r>1 && (maze[r-1][c]==-1 || maze[r-1][c]==t)) {    // up
        vector<unsigned char> sln1(sln); set<unsigned short> s1(s);
        if (search(r-1, c, 7-t, f, sln1, s1)) {
            sln = sln1;
            return true;
        }
    }
    if (r<m && (maze[r+1][c]==-1 || maze[r+1][c]==t)) {    // down
        vector<unsigned char> sln1(sln); set<unsigned short> s1(s);
        if (search(r+1, c, t, 7-f, sln1, s1)) {
            sln = sln1;
            return true;
        }
    }
    char t1 = left(f, t);
    if (c>1 && (maze[r][c-1]==-1 || maze[r][c-1]==t)) {    // left
        vector<unsigned char> sln1(sln); set<unsigned short> s1(s);
        if (search(r, c-1, f, t1, sln1, s1)) {
            sln = sln1;
            return true;
        }
    }
    if (c<n && (maze[r][c+1]==-1 || maze[r][c+1]==t)) {    // right
        vector<unsigned char> sln1(sln); set<unsigned short> s1(s);
        if (search(r, c+1, f, 7-t1, sln1, s1)) {
            sln = sln1;
            return true;
        }
    }
    visit.insert(v);
    return false;
}
 
int main()
{
    string name;
    while(cin >> name && name != "END") {
        cout << name << endl;
        cin >> m >> n >> r0 >> c0 >> t0 >> f0;
        for (char i=1; i<=m; ++i)
            for (char j=1; j<=n; ++j) {
                short v; cin >> v;
                maze[i][j] = v;
            }
        vector<unsigned char> sln; set<unsigned short> s;
        if (search(r0, c0, f0, t0, sln, s)) {
            short size = sln.size();
            for(short i=0; i<size; ++i) {
                if (i%9 == 0) cout << "  ";
                unsigned short r=sln[i]>>4, c=sln[i]&0xf;
                cout << '(' << r << ',' << c << ')';
                if (i != size-1) cout << ',';
                if (i%9 == 8 && i != size-1) cout << endl;
            }
            cout << endl;
        } else {
            cout << "  No Solution Possible" << endl;
        }
        visit.clear();
    }
    return 0;
}