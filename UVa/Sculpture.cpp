/**
 * UVa12171
 * 雕塑
 */

#include <iostream>
#include <tuple>
#include <map>
#include <set>
#include <functional>
#define p2 pair<short, short>
#define p3 tuple<short, short, short>

int main()
{
    using namespace std;
    short t; cin >> t;
    while(t--){
        short m[2][3]={{1000,1000,1000},{1,1,1}}, n; cin >> n;
        map<p2, set<short> > mx, my, mz;
        for(short i=0; i<n; ++i){
            short x0, y0, z0, x, y, z; cin >> x0 >> y0 >> z0 >> x >> y >> z; x += x0; y += y0; z += z0;
            for(short j=y0; j<y; ++j) for(short k=z0; k<z; ++k) mx[p2(j,k)].insert(x0), mx[p2(j,k)].insert(x);
            for(short j=x0; j<x; ++j) for(short k=z0; k<z; ++k) my[p2(j,k)].insert(y0), my[p2(j,k)].insert(y);
            for(short j=x0; j<x; ++j) for(short k=y0; k<y; ++k) mz[p2(j,k)].insert(z0), mz[p2(j,k)].insert(z);
            if(x0 < m[0][0]) m[0][0] = x0; if(x > m[1][0]) m[1][0] = x;
            if(y0 < m[0][1]) m[0][1] = y0; if(y > m[1][1]) m[1][1] = y;
            if(z0 < m[0][2]) m[0][2] = z0; if(z > m[1][2]) m[1][2] = z;
        }
        int s=0; set<p3 > visit;
        function<void(short, short, short)> search = [&](short x, short y, short z){
            if(z<m[1][2]){
                if(!mz[p2(x,y)].count(z+1)){ p3 p = make_tuple(x, y, z+1);
                    if(!visit.count(p)) visit.insert(p), search(x, y, z+1);
                } else ++s;
            }
            if(z>=m[0][2]){
                if(!mz[p2(x,y)].count(z)){ p3 p = make_tuple(x, y, z-1);
                    if(!visit.count(p)) visit.insert(p), search(x, y, z-1);
                } else ++s;
            }
            if(y<m[1][1]){
                if(!my[p2(x,z)].count(y+1)){ p3 p = make_tuple(x, y+1, z);
                    if(!visit.count(p)) visit.insert(p), search(x, y+1, z);
                } else ++s;
            }
            if(y>=m[0][1]){
                if(!my[p2(x,z)].count(y)){ p3 p = make_tuple(x, y-1, z);
                    if(!visit.count(p)) visit.insert(p), search(x, y-1, z);
                } else ++s;
            }
            if(x<m[1][0]){
                if(!mx[p2(y,z)].count(x+1)){ p3 p = make_tuple(x+1, y, z);
                    if(!visit.count(p)) visit.insert(p), search(x+1, y, z);
                } else ++s;
            }
            if(x>=m[0][0]){
                if(!mx[p2(y,z)].count(x)){ p3 p = make_tuple(x-1, y, z);
                    if(!visit.count(p)) visit.insert(p), search(x-1, y, z);
                } else ++s;
            }
        };
        search(m[0][0]-1, m[0][1]-1, m[0][2]-1);
        cout << s << ' ' << ((m[1][0]-m[0][0]+2)*(m[1][1]-m[0][1]+2)*(m[1][2]-m[0][2]+2)-visit.size()) << endl;
    }
    return 0;
}