/**
 * UVa11211
 * 数字逻辑
 */

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define N 16
int y[N][3], v1[N], v2[N], r[4], rr[4], a[4], out[4], n, t, m, cc, ans, kase = 0;
struct node {short k[N], a[N], b[N], c[N], m; int v[N]; bool f[N];} q[1000000];

struct cmp {
    bool operator() (int i, int j) const {
        for (int k=0; k<ans; ++k) v1[k] = q[i].v[k+5], v2[k] = q[j].v[k+5];
        sort(v1, v1+ans); sort(v2, v2+ans);
        for (int k=0; k<ans; ++k) if (v1[k] != v2[k]) return v1[k] < v2[k];
        return false;
    }
};
set<int, cmp> ss;

bool check(int p) {
    m = q[t].v[p] = 0;
    for (int i=0; i<N; ++i) q[t].v[p] |= y[q[t].k[p]][(q[t].v[q[t].a[p]]>>i&1) + (q[t].v[q[t].b[p]]>>i&1)] << i;
    for (int i=1; i<p; ++i) if (q[t].v[i] == q[t].v[p]) return false;
    if (q[t].v[p] != r[0] && q[t].v[p] != r[1] && q[t].v[p] != r[2] && q[t].v[p] != r[3]) q[t].f[p] = true;
    for (int i=5; i<=p; ++i) if (q[t].f[i] && (q[t].k[i] > q[t].k[p] || ans==6 || (ans==5 && m>1) || ++m > 3)) return false;
    return true;
}

bool ext(const node &e, int p, int i, int j, int k) {
    q[t] = e; q[t].k[p] = i; q[t].a[p] = j; q[t].b[p] = k; --q[t].c[i]; q[t].f[j] = q[t].f[k] = q[t].f[p] = false;
    if (check(p) && !ss.count(t)) {
        for (int i=0; i<cc; ++i) if (q[t].v[p] == rr[i]) ++q[t].m;
        if (q[t].m == cc) return true;
        if (q[t].m >= cc-6+ans) ss.insert(t++);
    }
    return false;
}

bool ext(const node &e) {
    int p = ans+4, m = 0;
    for (int i=5; i<p; ++i) if (e.f[i]) a[m++] = i;
    for (int i=1; i<=n; ++i) if (e.c[i] > 0) {
        if (ans == 6 && m) {
            if (m == 1) {
                for (int j=1; j<p; ++j) if ((j<5 || !e.f[j]) && ext(e, p, i, max(a[0], j), min(a[0], j))) return true;
            } else if (ext(e, p, i, a[1], a[0])) return true;
        } else if (m == 3) {
            if (ext(e, p, i, a[2], a[1]) || ext(e, p, i, a[2], a[0]) || ext(e, p, i, a[1], a[0])) return true;
            while (m--) for (int j=1; j<p; ++j) if ((j<5 || !e.f[j]) && ext(e, p, i, max(a[m], j), min(a[m], j))) return true;
        } else for (int j=1; j<p; ++j) for (int k=1; k<=j; ++k) if (ext(e, p, i, j, k)) return true;
    }
    return false;
}

void print() {
    for (int i=0, k=ans+5; i<4; ++i) for (int j=1; j<k; ++j) if (q[t].v[j] == r[i]) {
        out[i] = j; break;
    }
    cout << "Case " << ++kase << ": " << ans << endl;
    for (int i=5, j=ans+5; i<j; ++i) cout << i << ' ' << q[t].k[i] << ' ' << q[t].a[i] << ' ' << q[t].b[i] << endl;
    cout << out[0] << ' ' << out[1] << ' ' << out[2] << ' ' << out[3] << endl << endl;
}

void solve() {
    for (int i=1; i<=n; ++i) cin >> q[0].c[i] >> y[i][0] >> y[i][1] >> y[i][2];
    for (int i=q[t=0].m=0; i<4; ++i) r[i] = 0, q[0].v[i+1] = 0;
    for (int i=ans=0; i<N; ++i) {
        int v; cin >> v; r[0] |= v>>3<<i; r[1] |= (v>>2&1)<<i; r[2] |= (v>>1&1)<<i; r[3] |= (v&1)<<i;
        q[0].v[1] |= i>>3<<i; q[0].v[2] |= (i>>2&1)<<i; q[0].v[3] |= (i>>1&1)<<i; q[0].v[4] |= (i&1)<<i;
    }
    rr[0] = r[0]; rr[1] = r[1]; rr[2] = r[2]; rr[3] = r[3]; sort(rr, rr+4); cc = unique(rr, rr+4) - rr;
    for (int i=0; i<cc; ++i) for (int j=1; j<=4; ++j) if (rr[i] == q[0].v[j]) {
        ++q[0].m; break;
    }
    if (q[0].m == cc) return print();
    ss.clear();
    for (int h=0, c=ans=t=1; h<c;) {
        if (ext(q[h])) return print();
        if (++h == c) c = t, ++ans, ss.clear();
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}