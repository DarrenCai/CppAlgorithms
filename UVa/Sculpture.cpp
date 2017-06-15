/**
 * UVa12171
 * 雕塑
 */

#include <iostream>
#include <map>

int main()
{
    using namespace std;
    short t; cin >> t;
    while(t--){
        short m[3][2]={{1000,1},{1000,1},{1000,1}}, n; cin >> n;
        map<short, map<short, short> > mx, my, mz;
        for(short i=0; i<n; ++i){
            short x0, y0, z0, x, y, z; cin >> x0 >> y0 >> z0 >> x >> y >> z; x += x0; y += y0; z += z0;
            for(short j=y0; j<y; ++j) for(short k=z0; k<z; ++k) mx[y0][j] = mx[y][j] = k;
            for(short j=x0; j<x; ++j) for(short k=z0; k<z; ++k) my[x0][j] = my[x][j] = k;
            for(short j=x0; j<x; ++j) for(short k=y0; k<y; ++k) mz[x0][j] = mz[x][j] = k;
            if(x0 < m[0][0]) m[0][0] = x0; if(x > m[0][0]) m[0][0] = x;
            if(y0 < m[1][0]) m[1][0] = y0; if(y > m[1][0]) m[1][0] = y;
            if(z0 < m[2][0]) m[2][0] = z0; if(z > m[2][0]) m[2][0] = z;
        }
        //
    }
    return 0;
}