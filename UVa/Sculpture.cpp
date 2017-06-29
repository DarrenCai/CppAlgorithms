/**
 * UVa12171
 * 雕塑
 */

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>

int main()
{
    using namespace std;
#define p pair<short, short>
    short t; cin >> t;
    while(t--){
        short n; cin >> n; vector<vector<short> > boxs(n); set<short> sx, sy, sz; map<p, set<short> > mx, my, mz;
        for(short i=0; i<n; ++i){
            short x0, y0, z0, x, y, z; cin >> x0 >> y0 >> z0 >> x >> y >> z; x += x0; y += y0; z += z0;
            sx.insert(x0); sx.insert(x); sy.insert(y0); sy.insert(y); sz.insert(z0); sz.insert(z); boxs[i] = {x0, x, y0, y, z0, z};
        }
        short nx=sx.size()+1, ny=sy.size()+1, nz=sz.size()+1; vector<short> vx(nx+1), vy(ny+1), vz(nz+1);
        vx[0]=*sx.begin()-1; short i=1; for(auto x: sx) vx[i++]=x; vx[i]=*sx.rbegin()+1;
        vy[0]=*sy.begin()-1; i=1; for(auto y: sy) vy[i++]=y; vy[i]=*sy.rbegin()+1;
        vz[0]=*sz.begin()-1; i=1; for(auto z: sz) vz[i++]=z; vz[i]=*sz.rbegin()+1;
        for(short i=0; i<n; ++i){
            for(short j=lower_bound(vx.begin(),vx.end(),boxs[i][0])-vx.begin(); vx[j]!=boxs[i][1]; ++j){
                for(short k=lower_bound(vy.begin(),vy.end(),boxs[i][2])-vy.begin(); vy[k]!=boxs[i][3]; ++k)
                    mz[p(j,k)].insert(boxs[i][4]), mz[p(j,k)].insert(boxs[i][5]);
                for(short k=lower_bound(vz.begin(),vz.end(),boxs[i][4])-vz.begin(); vz[k]!=boxs[i][5]; ++k)
                    my[p(j,k)].insert(boxs[i][2]), my[p(j,k)].insert(boxs[i][3]);
            }
            for(short j=lower_bound(vy.begin(),vy.end(),boxs[i][2])-vy.begin(); vy[j]!=boxs[i][3]; ++j)
                for(short k=lower_bound(vz.begin(),vz.end(),boxs[i][4])-vz.begin(); vz[k]!=boxs[i][5]; ++k) mx[p(j,k)].insert(boxs[i][0]), mx[p(j,k)].insert(boxs[i][1]);
        }
        int s=0, v=0; set<tuple<short, short, short> > visit;
        static function<void(short, short, short)> search = [&](short x, short y, short z){
            visit.insert(make_tuple(x, y, z));
            v += (vx[x+1]-vx[x])*(vy[y+1]-vy[y])*(vz[z+1]-vz[z]);
            if(z+1 < nz){
                if(!mz.count(p(x, y)) || !mz[p(x, y)].count(vz[z+1])){
                    if(!visit.count(make_tuple(x, y, z+1))) search(x, y, z+1);
                }else s += (vx[x+1]-vx[x])*(vy[y+1]-vy[y]);
            }
            if(y+1 < ny){
                if(!my.count(p(x, z)) || !my[p(x, z)].count(vy[y+1])){
                    if(!visit.count(make_tuple(x, y+1, z))) search(x, y+1, z);
                }else s += (vx[x+1]-vx[x])*(vz[z+1]-vz[z]);
            }
            if(x+1 < nx){
                if(!mx.count(p(y, z)) || !mx[p(y, z)].count(vx[x+1])){
                    if(!visit.count(make_tuple(x+1, y, z))) search(x+1, y, z);
                }else s += (vy[y+1]-vy[y])*(vz[z+1]-vz[z]);
            }
            if(z > 0){
                if(!mz.count(p(x, y)) || !mz[p(x, y)].count(vz[z])){
                    if(!visit.count(make_tuple(x, y, z-1))) search(x, y, z-1);
                }else s += (vx[x+1]-vx[x])*(vy[y+1]-vy[y]);
            }
            if(y > 0){
                if(!my.count(p(x, z)) || !my[p(x, z)].count(vy[y])){
                    if(!visit.count(make_tuple(x, y-1, z))) search(x, y-1, z);
                }else s += (vx[x+1]-vx[x])*(vz[z+1]-vz[z]);
            }
            if(x > 0){
                if(!mx.count(p(y, z)) || !mx[p(y, z)].count(vx[x])){
                    if(!visit.count(make_tuple(x-1, y, z))) search(x-1, y, z);
                }else s += (vy[y+1]-vy[y])*(vz[z+1]-vz[z]);
            }
        };
        search(0, 0, 0); cout << s << ' ' << ((vx[nx]-vx[0])*(vy[ny]-vy[0])*(vz[nz]-vz[0])-v) << endl;
    }
    return 0;
}