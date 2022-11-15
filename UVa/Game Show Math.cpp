/**
 * UVa10400
 */

#include <iostream>
#include <cstring>
using namespace std;

#define M 32001
#define N 102
int d[N][M<<1], a[N], n, t; bool vis[N][M<<1]; char op[]="0+-*/";

int dp(int i, int x) {
    if (i == 0) return a[0] == x;
    int x0 = x+M;
    if (vis[i][x0]) return d[i][x0];
    vis[i][x0] = true;
    int y = x*a[i];
    if (abs(y) < M && dp(i-1, y)) return d[i][x0] = 4;
    if (a[i] && x%a[i]==0 && dp(i-1, x/a[i])) return d[i][x0] = 3;
    y = x+a[i];
    if (abs(y) < M && dp(i-1, y)) return d[i][x0] = 2;
    y = x-a[i];
    if (abs(y) < M && dp(i-1, y)) return d[i][x0] = 1;
    return d[i][x0] = 0;
}

int get(int op, int a, int x) {
    return op==1 ? x-a : (op==2 ? x+a : (op==3 ? x/a : x*a));
}

void print(int i, int x) {
    if (i > 0) {
        print(i-1, get(d[i][x+M], a[i], x));
        cout << op[d[i][x+M]] << a[i];
    } else cout << x;
}

void solve() {
    cin >> n;
    for (int i=0; i<n; ++i) cin >> a[i];
    cin >> t;
    memset(vis, 0, sizeof(vis));
    if (dp(n-1, t)) {
        print(n-1, t); cout << '=' << t << endl;
    } else cout << "NO EXPRESSION" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}