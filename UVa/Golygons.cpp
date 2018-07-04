/**
 * UVa225
 * 黄金图形
 */

#include <iostream>
#include <cstring>
using namespace std;

short n, k, r; bool blockX[311][311], blockY[311][311], visit[311][311] = {0}; char path[21]={0};

bool blockedX(int x1, int x2, int y) {
    if (x2 == x1) {
        return blockY[155+y][155+x1];
    } else if (x2 == x1+1) {
        return blockY[155+y][155+x1] || blockY[155+y][155+x2];
    } else {
        int l = (x2-x1)>>1;
        return blockedX(x1, x1+l, y) || blockedX(x1+l+1, x2, y);
    }
}

bool blockedY(int y1, int y2, int x) {
    if (y2 == y1) {
        return blockX[155+x][155+y1];
    } else if (y2 == y1+1) {
        return blockX[155+x][155+y1] || blockX[155+x][155+y2];
    } else {
        int l = (y2-y1)>>1;
        return blockedY(y1, y1+l, x) || blockedY(y1+l+1, y2, x);
    }
}

void dfs(short d=0, int x=0, int y=0) {
    if (!d) {
        if (!blockedX(1, 1, 0)) {
            path[0] = 'e'; visit[156][155] = true;
            dfs(1, 1, 0);
            path[0] = 0; visit[156][155] = false;
        }
        if (!blockedY(1, 1, 0)) {
            path[0] = 'n'; visit[155][156] = true;
            dfs(1, 0, 1);
            path[0] = 0; visit[155][156] = false;
        }
        if (!blockedY(-1, -1, 0)) {
            path[0] = 's'; visit[155][154] = true;
            dfs(1, 0, -1);
            path[0] = 0; visit[155][154] = false;
        }
        if (!blockedX(-1, -1, 0)) {
            path[0] = 'w'; visit[154][155] = true;
            dfs(1, -1, 0);
            path[0] = 0; visit[154][155] = false;
        }
    } else if (d == n) {
        if (!x && !y) {
            cout << path << endl; ++r;
        }
    } else if (x || y) {
        if (path[d-1]=='e' || path[d-1]=='w') {
            int t = y+d+1;
            if (!blockedY(y+1, t, x) && !visit[155+x][155+t]) {
                path[d] = 'n'; visit[155+x][155+t] = true;
                dfs(d+1, x, t);
                path[d] = 0; visit[155+x][155+t] = false;
            }
            t = y-d-1;
            if (!blockedY(t, y-1, x) && !visit[155+x][155+t]) {
                path[d] = 's'; visit[155+x][155+t] = true;
                dfs(d+1, x, t);
                path[d] = 0; visit[155+x][155+t] = false;
            }
        } else {
            int t = x+d+1;
            if (!blockedX(x+1, t, y) && !visit[155+t][155+y]) {
                path[d] = 'e'; visit[155+t][155+y] = true;
                dfs(d+1, t, y);
                path[d] = 0; visit[155+t][155+y] = false;
            }
            t = x-d-1;
            if (!blockedX(t, x-1, y) && !visit[155+t][155+y]) {
                path[d] = 'w'; visit[155+t][155+y] = true;
                dfs(d+1, t, y);
                path[d] = 0; visit[155+t][155+y] = false;
            }
        }
    }
}

int main()
{
    freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        memset(blockX, 0, sizeof(blockX));
        memset(blockY, 0, sizeof(blockY));
        cin >> n >> k;
        for (short i=0; i<k; ++i) {
            int a, b; cin >> a >> b;
            if (a>=-155 && a<=155 && b>=-155 && b<=155)
                blockX[155+a][155+b] = blockY[155+b][155+a] = true;
        }
        r = 0; dfs();
        cout << "Found " << r << " golygon(s)." << endl << endl;
    }
    return 0;
}