/**
 * UVa1634
 * 野餐
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 110

struct point {
    short x, y;
    bool operator< (const point& rhs) const {
        return y<rhs.y || (y==rhs.y && x<rhs.x);
    }
} s[N], p0, p1;
int cross(int x1, int y1, int x2, int y2) {
    return x1*y2 - x2*y1;
}
int dot(int x1, int y1, int x2, int y2) {
    return x1*x2 + y1*y2;
}
bool cmp(short a, short b) {
    int da = dot(s[a].x-p0.x, s[a].y-p0.y, p1.x-p0.x, p1.y-p0.y);
    int db = dot(s[b].x-p0.x, s[b].y-p0.y, p1.x-p0.x, p1.y-p0.y);
    if (da < 0 && db >= 0) return false;
    if (db < 0 && da >= 0) return true;
    long long ca = cross(s[a].x-p0.x, s[a].y-p0.y, p1.x-p0.x, p1.y-p0.y);
    long long cb = cross(s[b].x-p0.x, s[b].y-p0.y, p1.x-p0.x, p1.y-p0.y);
    long long t1 = ca * ca * ((s[b].x-p0.x)*(s[b].x-p0.x) + (s[b].y-p0.y)*(s[b].y-p0.y));
    long long t2 = cb * cb * ((s[a].x-p0.x)*(s[a].x-p0.x) + (s[a].y-p0.y)*(s[a].y-p0.y));
    if (t1 != t2) return da<0 ? t1>t2 : t1<t2;
    da = dot(s[a].x-p1.x, s[a].y-p1.y, p0.x-p1.x, p0.y-p1.y);
    db = dot(s[b].x-p1.x, s[b].y-p1.y, p0.x-p1.x, p0.y-p1.y);
    if (da < 0 && db >= 0) return true;
    if (db < 0 && da >= 0) return false;
    ca = cross(s[a].x-p1.x, s[a].y-p1.y, p0.x-p1.x, p0.y-p1.y);
    cb = cross(s[b].x-p1.x, s[b].y-p1.y, p0.x-p1.x, p0.y-p1.y);
    t1 = ca * ca * ((s[b].x-p1.x)*(s[b].x-p1.x) + (s[b].y-p1.y)*(s[b].y-p1.y));
    t2 = cb * cb * ((s[a].x-p1.x)*(s[a].x-p1.x) + (s[a].y-p1.y)*(s[a].y-p1.y));
    return da<0 ? t1<t2 : t1>t2;
}
bool cmp2(short a, short b) {
    int da = dot(s[a].x-p0.x, s[a].y-p0.y, p1.x-p0.x, p1.y-p0.y);
    int db = dot(s[b].x-p0.x, s[b].y-p0.y, p1.x-p0.x, p1.y-p0.y);
    if (da < 0 && db >= 0) return false;
    if (db < 0 && da >= 0) return true;
    long long ca = cross(s[a].x-p0.x, s[a].y-p0.y, p1.x-p0.x, p1.y-p0.y);
    long long cb = cross(s[b].x-p0.x, s[b].y-p0.y, p1.x-p0.x, p1.y-p0.y);
    long long t1 = ca * ca * ((s[b].x-p0.x)*(s[b].x-p0.x) + (s[b].y-p0.y)*(s[b].y-p0.y));
    long long t2 = cb * cb * ((s[a].x-p0.x)*(s[a].x-p0.x) + (s[a].y-p0.y)*(s[a].y-p0.y));
    return da<0 ? t1>t2 : t1<t2;
}
int d[N][N][2], dd[N][N][N][2], ds[N][N][N], ans; bool f[N][N]; short ss1[N], ss2[N], ss3[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n; cin >> n;
    while (n--) {
        short m; cin >> m;
        for (short i=0; i<m; ++i) cin >> s[i].x >> s[i].y;
        sort(s, s+m);
        ans = 0; memset(f, false, sizeof(f)); memset(d, 0, sizeof(d)); memset(dd, 0, sizeof(dd));
        for (short i=0; i<m; ++i) for (short j=i+2; j<m; ++j) {
            p0 = s[i]; p1 = s[j];
            short t1=0, t2 = 0, np = -1, pp = -1;
            for (short k=i+1; k<j; ++k) {
                ds[i][j][k] = cross(s[k].x-s[i].x, s[k].y-s[i].y, s[j].x-s[i].x, s[j].y-s[i].y);
                if (ds[i][j][k] == 0) f[i][j] = true;
                else if (ds[i][j][k] > 0) ss1[t1++] = k;
                else ss2[t2++] = k;
            }
            if (t1) sort(ss1, ss1+t1, cmp);
            if (t2) sort(ss2, ss2+t2, cmp);
            point t = p1; p1 = p0; p0 = t;
            for (short k=0; k<t1; ++k) {
                if (pp < 0 || cmp2(ss1[k], pp)) pp = ss1[k];
                else ds[i][j][ss1[k]] = 0;
            }
            for (short k=0; k<t2; ++k) {
                if (np < 0 || cmp2(ss2[k], np)) np = ss2[k];
                else ds[i][j][ss2[k]] = 0;
            }
        }
        for (short l=2; l<m; ++l) for (short i=0, j; (j=i+l)<m; ++i) for (short k=i+1; k<j; ++k)
            if (ds[i][j][k] > 0) {
                if (!f[i][k]) for (short k2=i+1; k2<k; ++k2)
                    if (ds[i][k][k2] > 0 && cross(s[j].x-s[k].x, s[j].y-s[k].y, s[k2].x-s[k].x, s[k2].y-s[k].y) >= 0) {
                        dd[i][k][j][0] = max(dd[i][k][j][0], dd[i][k2][k][0]+ds[i][k][k2]);
                    }
            } else if (ds[i][j][k] < 0) {
                if (!f[i][k]) for (short k2=i+1; k2<k; ++k2)
                    if (ds[i][k][k2] < 0 && cross(s[j].x-s[k].x, s[j].y-s[k].y, s[k2].x-s[k].x, s[k2].y-s[k].y) <= 0) {
                        dd[i][k][j][1] = max(dd[i][k][j][1], dd[i][k2][k][1]-ds[i][k][k2]);
                    }
            }
        for (short l=2; l<m; ++l) for (short i=0, j; (j=i+l)<m; ++i) {
            for (short k=i+1; k<j; ++k)
                if (ds[i][j][k] > 0) {
                    d[i][j][0] = max(d[i][j][0], ds[i][j][k]);
                    if (!f[i][k]) d[i][j][0] = max(d[i][j][0], dd[i][k][j][0]+ds[i][j][k]);
                } else if (ds[i][j][k] < 0) {
                    d[i][j][1] = max(d[i][j][1], -ds[i][j][k]);
                    if (!f[i][k]) d[i][j][1] = max(d[i][j][1], dd[i][k][j][1]-ds[i][j][k]);
                }
            ans = max(ans, max(d[i][j][0], d[i][j][1]));
            if (!f[i][j]) ans = max(ans, d[i][j][0] + d[i][j][1]);
        }
        cout << (ans>>1) << (ans&1 ? ".5" : ".0") << endl;
    }
    return 0;
}