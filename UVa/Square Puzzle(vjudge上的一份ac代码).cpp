/**
 * UVa10639
 * 正方形拼图
 * vjudge上的一份ac代码 https://vjudge.net/solution/27856847
 */

#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for(int i = (l); i < (r); i++)
const double eps = 1e-6;
const double inf = 0x3f3f3f3f;
const int maxn = 10;
int n, m;
int dcmp(double x) {
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
class Point {
public:
    double x, y;
    Point(double xx = 0, double yy = 0) : x(xx), y(yy) {}
    Point operator+ (const Point &rhs) const {
        return Point(x+rhs.x, y+rhs.y);
    }
    Point operator- (const Point &rhs) const {
        return Point(x-rhs.x, y-rhs.y);
    }
    bool operator== (const Point &rhs) const {
        return dcmp(x-rhs.x) == 0 && dcmp(y-rhs.y) == 0;
    }
};

typedef Point Vector;
double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }

bool onSegment(Point p, Point a1, Point a2) {
    bool fl = dcmp( Cross(a1-p, a2-p) ) == 0 && dcmp( Dot(a1-p, a2-p) ) < 0;
    return fl || (p == a1) || (p == a2);
}

const int RD = 2, LD = 3, RU = 4, LU = 5;
const int DOWN = 1, UP = 2, RIGHT = 3, LEFT = 4;

class Poly {
public:
    int K;
    Point a[105];
    int mat[maxn][maxn];

    int check(const Point &p) const {
        int wn = 0;
        _for(i, 0, K) {
            if (onSegment(p, a[i], a[(i+1)%K]) ) return 2;
            int fl = dcmp( Cross(a[(i+1)%K]-a[i], p-a[i]) );
            int d1 = dcmp( a[i].y - p.y );
            int d2 = dcmp( a[(i+1)%K].y - p.y );
            if (fl > 0 && d1 <= 0 && d2 > 0) wn++;
            if (fl < 0 && d2 <= 0 && d1 > 0) wn--;
        }
        if (wn != 0) return 1;
        return 0;
    }

    void buildMap() {
        _for(i, 0, m) _for(j, 0, m) {
            Point mid( (double)(i) + .5, (double)(j) + .5 );
            Point lu( (double)(i) + .25, (double)(j) + .75 );
            Point ru( (double)(i) + .75, (double)(j) + .75 );
            Point ld( (double)(i) + .25, (double)(j) + .25 );
            Point rd( (double)(i) + .75, (double)(j) + .25 );
            
            if (check(mid) == 0) mat[i][j] = 0;
            else if (check(mid) == 1) mat[i][j] = 1;
            else if (check(ld) == 2 && check(ru) == 2 && check(rd) == 1) mat[i][j] = RD;
            else if (check(lu) == 2 && check(rd) == 2 && check(ld) == 1) mat[i][j] = LD;
            else if (check(lu) == 2 && check(rd) == 2 && check(ru) == 1) mat[i][j] = RU;
            else mat[i][j] = LU;
        }
    }

    double Area() {
        double ans = .0;
        _for(i, 0, m) _for(j, 0, m) {
            if (mat[i][j] == 1) ans += 1;
            else if (mat[i][j] != 0) ans += 0.5;
        }
        return ans;
    }
    void normalize() {
        double xmin = inf, ymin = inf;
        _for(i, 0, K) {
            xmin = min(xmin, a[i].x);
            ymin = min(ymin, a[i].y);
        }
        _for(i, 0, K) {
            a[i].x -= xmin;
            a[i].y -= ymin;
            assert(0 <= a[i].x && a[i].x <= m);
            assert(0 <= a[i].y && a[i].y <= m);
        }
        buildMap();
    }
    void rotate() {
        _for(i, 0, K) {
            a[i] = Point(a[i].y, -a[i].x);
        }
        normalize();
    }

    bool Move(int dir) {
        if (dir == DOWN) {
            _for(i, 0, m) if (mat[i][0] != 0) return false;
            _for(j, 0, m-1) {
                _for(i, 0, m) mat[i][j] = mat[i][j+1];
            }
            _for(i, 0, m) mat[i][m-1] = 0;
        }
        if (dir == UP) {
            _for(i, 0, m) if (mat[i][m-1] != 0) return false;
            for (int j = m-1; j > 0; j--) {
                _for(i, 0, m) mat[i][j] = mat[i][j-1];
            }
            _for(i, 0, m) mat[i][0] = 0;
        }
        if (dir == RIGHT) {
            _for(i, 0, m) if (mat[m-1][i] != 0) return false;
            for (int i = m-1; i > 0; i--) {
                _for(j, 0, m) mat[i][j] = mat[i-1][j];
            }
            _for(i, 0, m) mat[0][i] = 0;
        }
        if (dir == LEFT) {
            _for(i, 0, m) if (mat[0][i] != 0) return false;
            _for(i, 0, m-1) {
                _for(j, 0, m) mat[i][j] = mat[i+1][j];
            }
            _for(i, 0, m) mat[m-1][i] = 0;
        }
        return true;
    }
} poly[maxn];

vector<Poly> vec[maxn];
bool vis[maxn];

void getPolys() {
    _for(i, 0, maxn) vec[i].clear();
    memset(vis, 0, sizeof(vis));
    
    _for(i, 0, n) {
        Poly pp = poly[i];
        // enumerate posture
        _for(dir, 0, 4) {
            Poly plg = pp;

            while (true) {
                Poly plgp = plg;
                while (true) {
                   vec[i].push_back(plgp);
                   if (!plgp.Move(RIGHT)) break;
                }
                if (!plg.Move(UP)) break;
            }
            pp.rotate();
        }
    }    
}

class Node {
public:
    int mat[maxn][maxn];
    void init() {
        memset(mat, 0, sizeof(mat));
    }

    bool add(const Poly &p) {
        _for(i, 0, m) _for(j, 0, m) {
            if (mat[i][j] == 0) mat[i][j] = p.mat[i][j];
            else {
                if (p.mat[i][j] == 0) continue;
                else if (mat[i][j] + p.mat[i][j] == 7) mat[i][j] = 1;
                else return false;
            }
        }
        return true;
    }
} P;

bool dfs(int x, int y) {
    if (y == m) return true;
    bool ok = false;

    if (P.mat[x][y] == 1) {
        x++;
        if (x == m) {
            x = 0;
            y++;
        }
        return dfs(x, y);
    }
    for (int i = 0; i < n && !(ok); i++) {
        if (vis[i]) continue;
        for (auto u : vec[i]) {
            if (ok) break;
            Node P0 = P;
            // then try to insert
            if (P.mat[x][y] == 0 && u.mat[x][y] != 0 && P.add(u)) {
                vis[i] = true;
                if (u.mat[x][y] != 1) ok = dfs(x, y);
                else if (x == m-1) ok = dfs(0, y+1);
                else ok = dfs(x+1, y);
                vis[i] = false;
            } else if (P.mat[x][y] + u.mat[x][y] == 7 && P.add(u)) {
                vis[i] = true;
                if (x == m-1) ok = dfs(0, y+1);
                else ok = dfs(x+1, y);
                vis[i] = false;
            }
            P = P0;
        }
    }
    return ok;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int kase;
    scanf("%d", &kase);
    while (kase--) {
        scanf("%d%d", &n, &m);
        _for(i, 0, n) {
            scanf("%d", &poly[i].K);
            _for(j, 0, poly[i].K) {
                scanf("%lf%lf", &poly[i].a[j].x, &poly[i].a[j].y);
            }
        }

        double area = 0;
        _for(i, 0, n) {
            poly[i].normalize();
            area += poly[i].Area();
        }
        if (dcmp(area - (m * m))) {
            printf("no\n");
            continue;
        }

        P.init();
        getPolys();
        int res = dfs(0, 0);
        if (res) printf("yes\n");
        else printf("no\n");
    }
}