/**
 * UVa1604
 * 立体八数码问题
 */

#include <iostream>
using namespace std;

enum{B, W, R, E}; const char m[][2] = {{-1,0},{0,-1},{0,1},{1,0}}; int dest; short depth;

short offset(char r, char c) {
    return (r<<2)+(r<<1)+(c<<1);
}

short h(int cur) {
    short h = 0;
    for (char r=0; r<3; ++r)
        for (char c=0; c<3; ++c) {
            short o = offset(r, c), color1 = cur>>o&E, color2 = dest>>o&E;
            if (color1 != color2 && color2 != E) ++h;
        }
    return h;
}

bool IDAstar(char r, char c, int cur, int left = 0, short d=0, char pre=-1) {
    if (cur == dest) return true;
    if (d < depth)
        for (char i=0; i<4; ++i) {
            if (pre+i == 3) continue;
            char rr = r+m[i][0], cc=c+m[i][1];
            if (rr<0 || rr>2 || cc<0 || cc>2) continue;
            short o = offset(rr, cc), oo = offset(r, c), tColor = cur>>o&E, lColor = left>>o&E;
            if (i==0 || i==3) tColor = E - tColor - lColor;
            else { short t = tColor; tColor = lColor; lColor = t; }
            int next = ((cur | (E<<o)) ^ (E<<oo)) | (tColor<<oo);
            int ll = left ^ (E<<oo);
            if (d+h(next)<depth && IDAstar(rr, cc, next,
                (left ^ (left&E<<oo)) | (lColor<<oo), d+1, i)) return true;
        }
    return false;
}

int main()
{
    short x, y;
    while (cin>>x>>y && x) {
        --x; --y; dest = 0; int cur = 0x15555 | (E<<offset(y, x));
        for (char r=0; r<3; ++r)
            for (char c=0; c<3; ++c) {
                char color; cin>>color;
                if (color == 'W') dest |= W<<offset(r, c);
                else if (color == 'R') dest |= R<<offset(r, c);
                else if (color == 'E') dest |= E<<offset(r, c);
            }
        for (depth = h(cur); !IDAstar(y, x, cur) && depth<=30; ++depth);
        cout << (depth>30 ? -1: depth) << endl;
    }
    return 0;
}