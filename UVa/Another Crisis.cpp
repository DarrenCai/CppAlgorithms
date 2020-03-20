/**
 * UVa12186
 * 工人的请愿书
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define N 100010
vector<int> g[N];
int d[N], n, t;

bool cmp(int i, int j) {
    return d[i] < d[j];
}

int calc(int i) {
    if (g[i].size() == 0) return d[i] = 1;
    for (int j=g[i].size()-1; j>=0; --j) calc(g[i][j]);
    int c = (g[i].size() * t - 1) / 100 + 1;
    if (c < g[i].size()) sort(g[i].begin(), g[i].end(), cmp);
    d[i] = 0;
    for (int j=0; j<c; ++j) d[i] += d[g[i][j]];
    return d[i];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> t && n && t) {
        for (int i=0; i<=n; ++i) g[i].clear();
        for (int i=1; i<=n; ++i) {
            int u; cin >> u; g[u].push_back(i);
        }
        cout << calc(0) << endl;
    }
    return 0;
}