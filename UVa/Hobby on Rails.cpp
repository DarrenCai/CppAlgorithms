/**
 * LA4644/UVa1448
 * Regionals 2009 >> Asia - Tokyo
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 8
char g[N][N]; short s[N][2], r[N][N], p[N][N], n, w, h, ans;
struct node {short x, y, c, d;} a[N][N][3]; bool vis1[N][N], vis2[N][N][3][1<<N] = {0};

bool check(short v) {
    for (short i=0; i<n; ++i, v>>=2) {
        short x = s[i][0], y = s[i][1], rot = r[x][y] = v&3;
        if (x==0 && ((g[x][y]=='L' && rot!=2) || (g[x][y]=='R' && rot!=3))) return false;
        if (x==h-1 && ((g[x][y]=='L' && rot!=0) || (g[x][y]=='R' && rot!=1))) return false;
        if (y==0 && ((g[x][y]=='L' && rot!=1) || (g[x][y]=='R' && rot!=2))) return false;
        if (y==w-1 && ((g[x][y]=='L' && rot!=3) || (g[x][y]=='R' && rot!=0))) return false;
    }
    return true;
}

bool check(short x, short y, short nx, short ny) {
    char c = g[nx][ny]; short rot = r[nx][ny];
    if (c == 'S') {
        if (nx!=x && !rot) return false;
        if (ny!=y && rot) return false;
    } else if (c == 'C') {
        if (nx<x && rot!=2 && rot!=3) return false;
        if (ny>y && rot!=0 && rot!=3) return false;
        if (nx>x && rot!=0 && rot!=1) return false;
        if (ny<y && rot!=1 && rot!=2) return false;
    } else if (c == 'L') {
        if (nx<x && rot==0) return false;
        if (ny>y && rot==1) return false;
        if (nx>x && rot==2) return false;
        if (ny<y && rot==3) return false;
    } else {
        if (nx<x && rot==1) return false;
        if (ny>y && rot==2) return false;
        if (nx>x && rot==3) return false;
        if (ny<y && rot==0) return false;
    }
    return true;
}

short check(short x, short y) {
    bool f[] = {true, true, true, true}; char c = g[x][y]; short rot = r[x][y], ret = 4;
    if (rot == 0) f[c=='L' ? 2 : 1] = false;
    else if (rot == 1) f[c=='L' ? 3 : 2] = false;
    else if (rot == 2) f[c=='L' ? 0 : 3] = false;
    else f[c=='L' ? 1 : 0] = false;
    short nx = x-1;
    if (f[0]) {
        if (!vis1[nx][y]) ret = 0;
        else if (!check(x, y, nx, y)) return -1;
    } else if (vis1[nx][y] && check(x, y, nx, y)) return -1;
    short ny = y+1;
    if (f[1]) {
        if (!vis1[x][ny]) ret = 1;
        else if (!check(x, y, x, ny)) return -1;
    } else if(vis1[x][ny] && check(x, y, x, ny)) return -1;
    nx = x+1;
    if (f[2]) {
        if (!vis1[nx][y]) ret = 2;
        else if (!check(x, y, nx, y)) return -1;
    } else if (vis1[nx][y] && check(x, y, nx, y)) return -1;
    ny = y-1;
    if (f[3]) {
        if (!vis1[x][ny]) ret = 3;
        else if (!check(x, y, x, ny)) return -1;
    } else if(vis1[x][ny] && check(x, y, x, ny)) return -1;
    return ret;
}

void build() {
    memset(p, -1, sizeof(p));
    for (short i=0; i<n; ++i) p[s[i][0]][s[i][1]] = i;
    for (short i=0; i<n; ++i) {
        short x = s[i][0], y = s[i][1], nx[3], ny[3], px[] = {x, x, x}, py[] = {y, y, y};
        node (&b)[3] = a[x][y]; b[0].c = b[1].c = b[2].c = 0;
        if (r[x][y] == 0) {
            if (g[x][y] == 'L') {
                nx[0] = x; ny[0] = y+1; nx[1] = x-1; ny[1] = y; nx[2] = x; ny[2] = y-1;
            } else {
                nx[0] = x+1; ny[0] = y; nx[1] = x; ny[1] = y-1; nx[2] = x-1; ny[2] = y;
            }
        } else if (r[x][y] == 1) {
            if (g[x][y] == 'L') {
                nx[0] = x+1; ny[0] = y; nx[1] = x; ny[1] = y+1; nx[2] = x-1; ny[2] = y;
            } else {
                nx[0] = x; ny[0] = y-1; nx[1] = x-1; ny[1] = y; nx[2] = x; ny[2] = y+1;
            }
        } else if (r[x][y] == 2) {
            if (g[x][y] == 'L') {
                nx[0] = x; ny[0] = y-1; nx[1] = x+1; ny[1] = y; nx[2] = x; ny[2] = y+1;
            } else {
                nx[0] = x-1; ny[0] = y; nx[1] = x; ny[1] = y+1; nx[2] = x+1; ny[2] = y;
            }
        } else {
            if (g[x][y] == 'L') {
                nx[0] = x-1; ny[0] = y; nx[1] = x; ny[1] = y-1; nx[2] = x+1; ny[2] = y;
            } else {
                nx[0] = x; ny[0] = y+1; nx[1] = x+1; ny[1] = y; nx[2] = x; ny[2] = y-1;
            }
        }
        for (short i=0; i<3; ++i) {
            x = nx[i]; y = ny[i]; short x0 = px[i], y0 = py[i];
            while (p[x][y] < 0) {
                ++b[i].c; short x1 = x, y1 = y;
                if (g[x][y] == 'S') {
                    x = (x<<1) - x0; y = (y<<1) - y0;
                } else {
                    if (x < x0) {
                        y = r[x][y]==2 ? y+1 : y-1;
                    } else if (x > x0) {
                        y = r[x][y]==1 ? y+1 : y-1;
                    } else if (y < y0) {
                        x = r[x][y]==2 ? x+1 : x-1;
                    } else {
                        x = r[x][y]==3 ? x+1 : x-1;
                    }
                }
                x0 = x1; y0 = y1;
            }
            ++b[i].c; b[i].x = x; b[i].y = y;
            if (r[x][y] == 0) b[i].d = g[x][y] == 'L' ? (y0<y ? 2 : x0<x) : (x0<x ? 2 : y0<y);
            else if (r[x][y] == 1) b[i].d = g[x][y] == 'L' ? (x0<x ? 2 : y0>y) : (y0>y ? 2 : x0<x);
            else if (r[x][y] == 2) b[i].d = g[x][y] == 'L' ? (y0>y ? 2 : x0>x) : (x0>x ? 2 : y0>y);
            else b[i].d = g[x][y] == 'L' ? (x0>x ? 2 : y0<y) : (y0<y ? 2 : x0>x);
        }
    }
}

void dfs(short x0, short y0, short d0, short s0, short x, short y, short d, short s, short c = 0) {
    if (vis2[x][y][d][s]) {
        if (x==x0 && y==y0 && d==d0 && s==s0) ans = max(ans, c);
        return;
    }
    node e = a[x][y][d]; short i = p[e.x][e.y]; vis2[x][y][d][s] = true;
    dfs(x0, y0, d0, s0, e.x, e.y, e.d<2 ? 2 : (s&(1<<i) ? 1 : 0), e.d<2 ? s : s^(1<<i), c+e.c);
    vis2[x][y][d][s] = false;
}

void dfs(short x, short y, short px, short py) {
    char c = g[x][y]; short nx, ny;
    if (c == 'S') {
        nx = (x<<1) - px; ny = (y<<1) - py;
        if (nx<0 || nx>=h || ny<0 || ny>=w) return;
        if (!vis1[nx][ny]) {
            vis1[nx][ny] = true;
            if (g[nx][ny] == 'S') {
                r[nx][ny] = r[x][y]; dfs(nx, ny, x, y);
            } else if (py < y) {
                r[nx][ny] = 0; dfs(nx, ny, x, y);
                r[nx][ny] = 3; dfs(nx, ny, x, y);
            } else if (py > y) {
                r[nx][ny] = 1; dfs(nx, ny, x, y);
                r[nx][ny] = 2; dfs(nx, ny, x, y);
            } else if (px < x) {
                r[nx][ny] = 0; dfs(nx, ny, x, y);
                r[nx][ny] = 1; dfs(nx, ny, x, y);
            } else {
                r[nx][ny] = 2; dfs(nx, ny, x, y);
                r[nx][ny] = 3; dfs(nx, ny, x, y);
            }
            vis1[nx][ny] = false;
            return;
        }
        if (!check(x, y, nx, ny)) return;
    } else if (c == 'C') {
        if (r[x][y] == 0) py<y ? (nx=x-1, ny=y) : (nx=x, ny=y-1);
        else if (r[x][y] == 1) py>y ? (nx=x-1, ny=y) : (nx=x, ny=y+1);
        else if (r[x][y] == 2) py>y ? (nx=x+1, ny=y) : (nx=x, ny=y+1);
        else py<y ? (nx=x+1, ny=y) : (nx=x, ny=y-1);
        if (nx<0 || nx>=h || ny<0 || ny>=w) return;
        if (!vis1[nx][ny]) {
            vis1[nx][ny] = true;
            if (g[nx][ny] == 'S') {
                r[nx][ny] = nx!=x; dfs(nx, ny, x, y);
            } else if (ny < y) {
                r[nx][ny] = 1; dfs(nx, ny, x, y);
                r[nx][ny] = 2; dfs(nx, ny, x, y);
            } else if (ny > y) {
                r[nx][ny] = 0; dfs(nx, ny, x, y);
                r[nx][ny] = 3; dfs(nx, ny, x, y);
            } else if (nx < x) {
                r[nx][ny] = 2; dfs(nx, ny, x, y);
                r[nx][ny] = 3; dfs(nx, ny, x, y);
            } else {
                r[nx][ny] = 0; dfs(nx, ny, x, y);
                r[nx][ny] = 1; dfs(nx, ny, x, y);
            }
            vis1[nx][ny] = false;
            return;
        }
        if (!check(x, y, nx, ny)) return;
    }
    short cc = n, f;
    for (short i=0; i<n; ++i) {
        short c = check(s[i][0], s[i][1]);
        if (c < 0) return;
        if (c < 4) cc = i, f = c;
    }
    if (cc == n) {
        build();
        for (short v=(1<<n)-1; v>=0; --v) for (short i=0; i<n; ++i) {
            dfs(s[i][0], s[i][1], 0, v, s[i][0], s[i][1], 0, v, 0);
            dfs(s[i][0], s[i][1], 1, v, s[i][0], s[i][1], 1, v, 0);
            dfs(s[i][0], s[i][1], 2, v, s[i][0], s[i][1], 2, v, 0);
        }
        return;
    }
    px = s[cc][0]; py = s[cc][1];
    if (f == 0) {
        vis1[x = px-1][y = py] = true;
        if (g[x][y] == 'S') {
            r[x][y] = 1; dfs(x, y, px, py);
        } else {
            r[x][y] = 2; dfs(x, y, px, py);
            r[x][y] = 3; dfs(x, y, px, py);
        }
        vis1[x][y] = false;
    } else if (f == 1) {
        vis1[x = px][y = py+1] = true;
        if (g[x][y] == 'S') {
            r[x][y] = 0; dfs(x, y, px, py);
        } else {
            r[x][y] = 0; dfs(x, y, px, py);
            r[x][y] = 3; dfs(x, y, px, py);
        }
        vis1[x][y] = false;
    } else if (f == 2) {
        vis1[x = px+1][y = py] = true;
        if (g[x][y] == 'S') {
            r[x][y] = 1; dfs(x, y, px, py);
        } else {
            r[x][y] = 0; dfs(x, y, px, py);
            r[x][y] = 1; dfs(x, y, px, py);
        }
        vis1[x][y] = false;
    } else {
        vis1[x = px][y = py-1] = true;
        if (g[x][y] == 'S') {
            r[x][y] = 0; dfs(x, y, px, py);
        } else {
            r[x][y] = 1; dfs(x, y, px, py);
            r[x][y] = 2; dfs(x, y, px, py);
        }
        vis1[x][y] = false;
    }
}

int solve() {
    bool ok = true; ans = 0;
    for (short i=n=0; i<h; ++i) for (short j=0; j<w; ++j) {
        cin >> g[i][j];
        if (g[i][j]=='L' || g[i][j]=='R') {
            s[n][0] = i; s[n++][1] = j;
            if ((i==0 || i==h-1) && (j==0 || j==w-1)) ok = false;
        }
    }
    if (!ok) return ans;
    memset(vis1, 0, sizeof(vis1));
    for (short i=0; i<n; ++i) vis1[s[i][0]][s[i][1]] = true;
    for (short v=(1<<n<<n)-1; v>=0; --v) if (check(v)) {
        dfs(s[0][0], s[0][1], s[0][0], s[0][1]);
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>w>>h && w) cout << solve() << endl;
    return 0;
}