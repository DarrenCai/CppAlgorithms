/**
 * UVa1008/LA2240
 * 一个烦人的问题
 * World Finals 2001
 */

#include <iostream>
#include <set>
using namespace std;

#define block(c) (c != '-' && c != '#')
int f[64], s[11], r, c, t; char name[30];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

struct node {
    char s[9][9], ch, d; int p, x, y;
    bool operator< (const node &e) const {
        for (int i=0; i<r; ++i) for (int j=1; j<c; ++j) if (s[i][j] != e.s[i][j]) return s[i][j] < e.s[i][j];
        return false;
    }
    void rem() {
        bool g = true;
        while (g) {
            for (int i=r-1; i>=0; --i) for (int j=1; j<c; ++j) if (block(s[i][j]))
                for (int k=i+1; k<r && s[k][j] == '-'; ++k) s[k][j] = s[k-1][j], s[k-1][j] = '-';
            g = false;
            for (int i=0, k=0; i<r; ++i) for (int j=1; j<c; ++j, ++k) f[k] = k;
            for (int i=0, k=0, cc=c-1; i<r; ++i) for (int j=1; j<c; ++j, ++k) if (block(s[i][j])) {
                if (s[i][j] == s[i-1][j]) f[find(k)] = find(k-cc);
                if (s[i][j] == s[i][j-1]) f[find(k)] = find(k-1);
            }
            for (int i=0, k=0, cc=c-1, x; i<r; ++i) for (int j=1; j<c; ++j, ++k)
                if ((x = find(k)) != k) g = true, s[i][j] = s[x/cc][x%cc+1] = '-';
        }
    }
    bool empty() const {
        for (int i=0; i<r; ++i) for (int j=1; j<c; ++j) if (block(s[i][j])) return false;
        return true;
    }
} q[1000000];

struct cmp {
    bool operator() (int i, int j) const {
        return q[i] < q[j];
    }
};

set<int, cmp> vis;

bool ext(const int h) {
    for (int i=0; i<r; ++i) for (int j=1; j<c; ++j) if (block(q[h].s[i][j])) {
        if (q[h].s[i][j-1] == '-') {
            q[t] = q[h]; q[t].ch = q[h].s[i][j]; q[t].d = 'L'; q[t].p = h; q[t].x = i; q[t].y = j;
            q[t].s[i][j-1] = q[h].s[i][j]; q[t].s[i][j] = '-'; q[t].rem();
            if (q[t].empty()) return true;
            if (!vis.count(t)) vis.insert(t++);
        }
        if (q[h].s[i][j+1] == '-') {
            q[t] = q[h]; q[t].ch = q[h].s[i][j]; q[t].d = 'R'; q[t].p = h; q[t].x = i; q[t].y = j;
            q[t].s[i][j+1] = q[h].s[i][j]; q[t].s[i][j] = '-'; q[t].rem();
            if (q[t].empty()) return true;
            if (!vis.count(t)) vis.insert(t++);
        }
    }
    return false;
}

void find(int x, int &d) {
    int dd = 0;
    if (q[x].p) find(q[x].p, dd);
    s[dd] = x; d = dd+1;
}

void output() {
    int d = 0; find(t, d);
    cout << name << ": Minimum solution length = " << d;
    for (int i=0; i<d; ++i) {
        if ((i&3) == 0) cout << endl;
        cout << '(' << q[s[i]].ch << ',' << q[s[i]].x << ',' << q[s[i]].y << ',' << q[s[i]].d << ')';
        if ((i&3) < 3) cout << ' ';
    }
    cout << endl;
}

void solve() {
    for (int i=0; i<r; ++i) for (int j=0; j<c; ++j) cin >> q[0].s[i][j];
    --r; --c; t = 1; vis.clear(); vis.insert(0);
    for (int h=0; h<t; ++h) if (ext(h)) return output();
    int cc = 1;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> r >> c >> name && r) solve();
    return 0;
}