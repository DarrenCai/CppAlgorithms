/**
 * UVa1406/LA4013
 * 整数序列
 * ChengDu 2007
 */

#include <iostream>
#include <cstring>
using namespace std;

int c[17][65537], p[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536}, n, kase = 0;

void add(int i, int x) {
    while (x <= p[i]) ++c[i][x], x += x&-x;
}

int query(int i, int x) {
    int s = 0;
    while (x > 0) s += c[i][x], x -= x&-x;
    return s;
}

void solve() {
    memset(c, 0, sizeof(c)); n = max(n, 0);
    for (int i=0; i<n; ++i) {
        int x; cin >> x;
        for (int i=1; i<17; ++i) add(i, (x&p[i]-1)+1);
    }
    char c; int t = 0, r, x; long long sum = 0;
    while (cin>>c && c!='E') {
        if (c == 'Q') {
            cin >> x; r = t & p[x]-1; r = query(x+1, p[x+1]-r) - query(x+1, p[x]-r);
            sum += t & p[x] ? n - r : r;
        } else cin >> x, t = t+x & p[16]-1;
    }
    cout << "Case " << ++kase << ": " << sum << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin>>n && n!=-1) solve();
    return 0;
}