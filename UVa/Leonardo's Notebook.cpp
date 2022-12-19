/**
 * UVa12103/LA3641
 * Leonardo的笔记本
 * NWERC 2006
 */

#include <iostream>
using namespace std;

#define N 27
char s[N]; int c[N]; bool vis[N];

bool solve() {
    cin >> s;
    for (int i=0; i<N; ++i) c[i] = vis[i] = 0;
    for (int i=N-2; i>=0; --i) if (!vis[i]) {
        int t = 1; vis[i] = true;
        for (int j=s[i]-'A'; j!=i; j=s[j]-'A', ++t) vis[j] = true;
        ++ c[t];
    }
    for (int i=2; i<N; i+=2) if (c[i] & 1) return false;
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) cout << (solve() ? "Yes" : "No") << endl;
    return 0;
}