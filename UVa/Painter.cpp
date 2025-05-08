/**
 * UVa1075/LA4125
 * 画家
 * World Finals >> 2008 - Banff
 */

#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define N 100100
#define eps 1e-6

int n, x, kase = 0;

struct point {
    int x, y;
    bool operator< (const point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
} p[N][3];

struct seg {
    point p1, p2; int t; double d;
    seg(const point& p1, const point& p2, const int t):p1(p1), p2(p2), t(t) {d = (p2.y-p1.y)/(p2.x+eps-p1.x);}
    double y() const {
        return p1.y + d*(x+eps-p1.x);
    }
    bool operator< (const seg& rhs) const {
        return y() < rhs.y();
    }
} bot({-N, -N}, {N, -N}, 0), top({-N, N}, {N, N}, 0);
multimap<seg, int>::iterator it[N][3];

struct evt {
    int v, t;
    bool operator< (const evt& e) const {
        return p[t][v].x < p[e.t][e.v].x || (p[t][v].x == p[e.t][e.v].x && v < e.v);
    }
} e[3*N];

bool seg_intersects(const seg& a, const seg& b) {
    if (a.t == b.t) return false;
    int x1 = a.p1.x, y1 = a.p1.y, x2 = a.p2.x, y2 = a.p2.y, x3 = b.p1.x, y3 = b.p1.y, x4 = b.p2.x, y4 = b.p2.y;
    long long cx = x2-x1, cy = y2-y1, dx = x4-x3, dy = y4-y3, c = cx*dy - cy*dx;
    if (c == 0) {
        if (cx*(y3-y1) != cy*(x3-x1)) return false;
        long long d = cx*cx + cy*cy, e = (x3-x1)*cx+(y3-y1)*cy, f = (x4-x1)*cx+(y4-y1)*cy;
        return max(min(e, f), 0ll) <= min(max(e, f), d);
    }
    long long d = (x3-x1)*dy - (y3-y1)*dx, e = cx*(y4-y1) - cy*(x4-x1);
    return c > 0 ? (d>=0 && d<=c && e>=0 && e<=c) : (d<=0 && d>=c && e<=0 && e>=c);
}

bool insert(multimap<seg, int>& s, const seg& e, int d, multimap<seg, int>::iterator& it) {
    multimap<seg, int>::iterator it1 = it = s.insert(make_pair(e, d)), it2 = it;
    if (seg_intersects(e, (--it1)->first) || seg_intersects(e, (++it2)->first)) return false;
    return true;
}

bool erase(multimap<seg, int>& s, const multimap<seg, int>::iterator& it) {
    multimap<seg, int>::iterator it1 = it, it2 = it;
    if (seg_intersects((--it1)->first, (++it2)->first)) return false;
    s.erase(it);
    return true;
}

int update(multimap<seg, int>::iterator& it1, multimap<seg, int>::iterator& it2) {
    multimap<seg, int>::iterator it = it1;
    it2->second = (--it)->second;
    return it1->second = it->second + 1;
}

int solve() {
    for (int i=1, j=0; i<=n; ++i, j+=3) {
        cin >> p[i][0].x >> p[i][0].y >> p[i][1].x >> p[i][1].y >> p[i][2].x >> p[i][2].y;
        sort(p[i], p[i]+3); e[j] = {0, i}; e[j+1] = {1, i}; e[j+2] = {2, i};
    }
    sort(e, e+3*n);
    multimap<seg, int> s; s.insert(make_pair(bot, 1)); s.insert(make_pair(top, 0));
    int d = 1;
    for (int i=0,j=3*n; i<j; ++i) {
        int v = e[i].v, t = e[i].t; x = p[t][v].x;
        if (v == 0) {
            if (!insert(s, {p[t][0], p[t][1], t}, 0, it[t][0])) return 0;
            if (!insert(s, {p[t][0], p[t][2], t}, 0, it[t][1])) return 0;
            multimap<seg, int>::iterator it1 = it[t][0];
            d = max(d, ++it1 == it[t][1] ? update(it[t][0], it[t][1]) : update(it[t][1], it[t][0]));
        } else if (v == 1) {
            if (!insert(s, {p[t][1], p[t][2], t}, it[t][0]->second, it[t][2])) return 0;
            if (!erase(s, it[t][0])) return 0;
        } else if (!erase(s, it[t][1])) return 0;
        else if (!erase(s, it[t][2])) return 0;
    }
    return d;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n && n >= 0) {
        int s = solve();
        s ? cout << "Case " << ++kase << ": " << s << " shades" << endl : cout << "Case " << ++kase << ": ERROR" << endl;
    }
    return 0;
}