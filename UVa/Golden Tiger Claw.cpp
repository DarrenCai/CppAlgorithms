/**
 * UVa11383
 * 少林决胜
 */

#include <iostream>
using namespace std;

#define INF 1000
#define N 502
int w[N][N], slack[N], lx[N], ly[N], p[N], n; bool s[N], t[N];

bool match(int i) {
    s[i] = true;
    for (int j=1; j<=n; ++j) if (!t[j]) {
        int d = lx[i] + ly[j] - w[i][j];
        if (d == 0) {
            t[j] = true;
            if (!p[j] || match(p[j])) {
                p[j] = i;
                return true;
            }
        } else slack[j] = min(slack[j], d);
    }
    return false;
}

void km() {
    for (int i=1; i<=n; ++i) {
        p[i] = lx[i] = ly[i] = 0;
        for (int j=1; j<=n; ++j) lx[i] = max(lx[i], w[i][j]);
    }
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) slack[j] = INF;
        while (true) {
            for (int j=1; j<=n; ++j) s[j] = t[j] = false;
            if (match(i)) break;
            int a = INF;
            for (int j=1; j<=n; ++j) if (!t[j]) a = min(a, slack[j]);
            for (int j=1; j<=n; ++j) {
                if (s[j]) lx[j] -= a;
                t[j] ? ly[j] += a : slack[j] -= a;
            }
        }
    }
}

void solve() {
    for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) cin >> w[i][j];
    km();
    int s = 0;
    for (int i=1; i<=n; ++i) s += lx[i] + ly[i];
    for (int i=1; i<=n; ++i)  {
        cout << lx[i];
        i<n ? cout << ' ' : cout << endl;
    }
    for (int i=1; i<=n; ++i) {
        cout << ly[i];
        i<n ? cout << ' ' : cout << endl;
    }
    cout << s << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin >> n) solve();
    return 0;
}