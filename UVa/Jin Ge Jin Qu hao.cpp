/**
 * UVa12563
 * 劲歌金曲
 */

#include <iostream>
using namespace std;

#define max(a, b) (a>b ? a:b)
#define N 55

struct node {
    short n, w;
    bool operator> (const node& rhs) const {
        return n > rhs.n || (n==rhs.n && w > rhs.w);
    }
};

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int T; cin >> T;
    for (int k=1; k<=T; ++k) {
        node f[10000] = {0}; int n, t; cin >> n >> t; --t;
        for (int i=0; i<n; ++i) {
            int v; cin >> v;
            for (int j=t; j>=v; --j) {
                node e = f[j-v];
                ++e.n; e.w += v;
                f[j] = max(e, f[j]);
            }
        }
        cout << "Case " << k << ": " << f[t].n+1 << ' ' << f[t].w+678 << endl;
    }
    return 0;
}