/**
 * P2761 软件补丁问题
 * 同UVa658 It’s not a Bug, it’s a Feature!
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define M 100
#define N 20
int d[1<<N], w[M], m, n; char s1[M][N+1], s2[M][N+1]; bool inq[1<<N];

bool check(int u, const char (&s)[N+1]) {
    for (int i=0; i<n; ++i) if ((s[i]=='+' && ~u&(1<<i)) || (s[i]=='-' && u&(1<<i))) return false;
    return true;
}

int state(int u, const char (&s)[N+1]) {
    int v = u;
    for (int i=0; i<n; ++i) {
        if (s[i]=='+') v |= 1<<i;
        else if (s[i]=='-') v ^= v&(1<<i);
    }
    return v;
}

int solve() {
    for (int i=0; i<m; ++i) cin >> w[i] >> s1[i] >> s2[i];
    memset(d, -1, sizeof(d)); memset(inq, 0, sizeof(inq)); d[(1<<n)-1] = 0;
    queue<int> q; q.push((1<<n)-1);
    while (!q.empty()) {
        int u = q.front(); q.pop(); inq[u] = false;
        for (int i=0; i<m; ++i) if (check(u, s1[i])) {
            int v = state(u, s2[i]);
            if (d[v] < 0 || d[v] > d[u]+w[i]) {
                d[v] = d[u]+w[i];
                if (!inq[v]) q.push(v), inq[v] = true;
            }
        }
    }
    return max(0, d[0]);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> m) cout << solve() << endl;
    return 0;
}