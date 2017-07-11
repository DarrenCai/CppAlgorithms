/**
 * UVa12171
 * 雕塑
 */

#include <iostream>
#include <algorithm>
#include <functional>

int main()
{
    using namespace std;
    short t; cin >> t;
    while(t--){
        short boxs[50][6], sx[102]={0}, sy[102]={0}, sz[102]={0}, n; cin >> n; 
        for(short i=0; i<n; ++i){ short j=i<<1, k=j+1;
            cin >> boxs[i][0] >> boxs[i][2] >> boxs[i][4] >> boxs[i][1] >> boxs[i][3] >> boxs[i][5]; boxs[i][1] += boxs[i][0]; boxs[i][3] += boxs[i][2]; boxs[i][5] += boxs[i][4];
            sx[j] = boxs[i][0]; sx[k] = boxs[i][1]; sy[j] = boxs[i][2]; sy[k] = boxs[i][3];  sz[j] = boxs[i][4]; sz[k] = boxs[i][5];
        }
        short m = (n<<1)+1; sort(sx, sx+m); sort(sy, sy+m); sort(sz, sz+m);
        const short nx = unique(sx, sx+m)-sx, ny = unique(sy, sy+m)-sy, nz = unique(sz, sz+m)-sz;
        sx[0]=sx[1]-1; sx[nx]=sx[nx-1]+1; sy[0]=sy[1]-1; sy[ny]=sy[ny-1]+1; sz[0]=sz[1]-1; sz[nz]=sz[nz-1]+1;
        bool mx[102][102][102]={0}, my[102][102][102]={0}, mz[102][102][102]={0}, visit[102][102][102]={0};
        for(short i=0; i<n; ++i){
            const short x = lower_bound(sx,sx+nx+1,boxs[i][0])-sx, y = lower_bound(sy,sy+ny+1,boxs[i][2])-sy, z = lower_bound(sz,sz+nz+1,boxs[i][4])-sz;
            for(short j=x; sx[j]!=boxs[i][1]; ++j){
                for(short k=y; sy[k]!=boxs[i][3]; ++k) mz[j][k][z] = true, mz[j][k][lower_bound(sz,sz+nz+1,boxs[i][5])-sz] = true;
                for(short k=z; sz[k]!=boxs[i][5]; ++k) my[j][k][y] = true, my[j][k][lower_bound(sy,sy+ny+1,boxs[i][3])-sy] = true;
            }
            for(short j=y; sy[j]!=boxs[i][3]; ++j) for(short k=z; sz[k]!=boxs[i][5]; ++k)
                mx[j][k][x] = true, mx[j][k][lower_bound(sx,sx+nx+1,boxs[i][1])-sx] = true;
        }
        int s=0, v=0;
        static function<void(short, short, short)> search = [&](short x, short y, short z){
            visit[x][y][z] = true;
            v += (sx[x+1]-sx[x])*(sy[y+1]-sy[y])*(sz[z+1]-sz[z]);
            if(z+1 < nz){
                if(!mz[x][y][z+1]){
                    if(!visit[x][y][z+1]) search(x, y, z+1);
                }else s += (sx[x+1]-sx[x])*(sy[y+1]-sy[y]);
            }
            if(y+1 < ny){
                if(!my[x][z][y+1]){
                    if(!visit[x][y+1][z]) search(x, y+1, z);
                }else s += (sx[x+1]-sx[x])*(sz[z+1]-sz[z]);
            }
            if(x+1 < nx){
                if(!mx[y][z][x+1]){
                    if(!visit[x+1][y][z]) search(x+1, y, z);
                }else s += (sy[y+1]-sy[y])*(sz[z+1]-sz[z]);
            }
            if(z > 0){
                if(!mz[x][y][z]){
                    if(!visit[x][y][z-1]) search(x, y, z-1);
                }else s += (sx[x+1]-sx[x])*(sy[y+1]-sy[y]);
            }
            if(y > 0){
                if(!my[x][z][y]){
                    if(!visit[x][y-1][z]) search(x, y-1, z);
                }else s += (sx[x+1]-sx[x])*(sz[z+1]-sz[z]);
            }
            if(x > 0){
                if(!mx[y][z][x]){
                    if(!visit[x-1][y][z]) search(x-1, y, z);
                }else s += (sy[y+1]-sy[y])*(sz[z+1]-sz[z]);
            }
        };
        search(0, 0, 0); cout << s << ' ' << ((sx[nx]-sx[0])*(sy[ny]-sy[0])*(sz[nz]-sz[0])-v) << endl;
    }
    return 0;
}