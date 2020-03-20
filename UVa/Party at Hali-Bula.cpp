/**
 * UVa1220
 * Hali-Bula的晚会
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

#define N 205
vector<short> g[N];
short d0[N], d1[N], n; bool f0[N], f1[N];

void calc(short i) {
    if (g[i].size() == 0) {
        d0[i] = 0; d1[i] = 1; f0[i] = f1[i] = true;
        return;
    }
    for (short j=g[i].size()-1; j>=0; --j) calc(g[i][j]);
    d0[i] = 0; f0[i] = true;
    for (short j=g[i].size()-1; j>=0; --j) {
        if (d0[g[i][j]] > d1[g[i][j]]) {
            d0[i] += d0[g[i][j]];
            if (!f0[g[i][j]]) f0[i] = false;
        } else if (d0[g[i][j]] == d1[g[i][j]]) {
            d0[i] += d0[g[i][j]];
            f0[i] = false;
        } else {
            d0[i] += d1[g[i][j]];
            if (!f1[g[i][j]]) f0[i] = false;
        }
    }
    d1[i] = 1; f1[i] = true;
    for (short j=g[i].size()-1; j>=0; --j) {
        d1[i] += d0[g[i][j]];
        if (!f0[g[i][j]]) f1[i] = false;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) {
        map<string, short> mp; string b[N], s, s1; cin >> s, mp[s] = 0;
        for (short i=1; i<n; ++i) cin >> s >> s1, b[i] = s1, mp[s] = i;
        for (short i=0; i<n; ++i) g[i].clear();
        for (short i=1; i<n; ++i) g[mp[b[i]]].push_back(i);
        calc(0);
        short max = d0[0]; bool f = f0[0];
        if (d0[0] == d1[0]) f = false;
        if (max < d1[0]) max = d1[0], f = f1[0];
        cout << max << ' ' << (f ? "Yes" : "No") << endl;
    }
    return 0;
}