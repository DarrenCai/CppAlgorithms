/**
 * UVa12559
 * 找黑圆
 */

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define min(a, b) (a<b ? a : b)
struct circle {
    int r, x, y;
    bool operator< (const circle& rhs) const {
        return r < rhs.r || (r==rhs.r && x<rhs.x) || (r==rhs.r && x==rhs.x && y<rhs.y);
    }
}ans[6];
int n, w, h;
char s[102][102];

void solve() {
    n = 0;
    for (int x=5; x<w-5; ++x) for (int y=5; y<h-5; ++y) for (int r=min(min(x, w-1-x), min(y, h-1-y)); r>=5; --r) {
        int sum = 0, acc = 0;
        for (int d=0; d<r; ++d) {
            double rf = 1.*r*r; int ff = sqrt(rf - d*d);
            for (int f=ff-1; f<=ff+1; ++f) if ((d-.5)*(d-.5)+(f-.5)*(f-.5)<rf && (d+.5)*(d+.5)+(f+.5)*(f+.5)>rf) {
                sum += 4;
                if (s[y+f][x+d] == '1') ++acc;
                if (s[y-f][x-d] == '1') ++acc;
                if (s[y-d][x+f] == '1') ++acc;
                if (s[y+d][x-f] == '1') ++acc;
            }
        }
        if (acc > .9 * sum) {
            ans[n].x = x; ans[n].y = y; ans[n++].r = r;
        }
    }
    sort(ans, ans + n);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin>>t;
    for (int i=1; i<=t; ++i) {
        cin >> w >> h;
        for (int j=0; j<h; ++j) cin >> s[j];
        solve();
        cout << "Case " << i << ": " << n;
        for (int i=0; i<n; ++i) cout << " (" << ans[i].r << ',' << ans[i].x << ',' << ans[i].y << ')';
        cout << endl;
    }
    return 0;
}