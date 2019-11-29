/**
 * UVa11536
 * 最短子序列
 */

#include <iostream>
#include <cstring>
#include <set>
using namespace std;

int a[1010], x[1000010] = {0, 1, 2, 3};

bool ok(int k) {
    for (int i=1; i<=k; ++i) if (!a[i]) return false;
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    for (int c=1; c<=t; ++c) {
        int n, m, k; cin >> n >> m >> k;
        memset(a, 0, sizeof(a)); a[1] = a[2] = a[3] = 1;
        for (int i=4; i<=n; ++i) ++a[x[i] = (x[i-1] + x[i-2] + x[i-3]) % m + 1];
        if (!ok(k)) {
            cout << "Case " << c << ": sequence nai" << endl;
        } else if (k <= 3) {
            cout << "Case " << c << ": " << k << endl;
        } else {
            memset(a, 0, sizeof(a)); a[1] = a[2] = a[3] = 1;
            set<int> s; s.insert(1); s.insert(2); s.insert(3); int h=1, b=3, min;
            while (s.size() < k) if (x[++b] <= k) s.insert(x[b]), ++a[x[b]];
            for (min=b; h <= n; ++h) {
                if (x[h] > k) {
                    int r = b - h; if (r < min) min = r;
                    continue;
                }
                if (--a[x[h]]) {
                    int r = b - h; if (r < min) min = r;
                } else {
                    while (++b <= n) {
                        ++ a[x[b]];
                        if (x[b] == x[h]) {
                            int r = b - h; if (r < min) min = r;
                            break;
                        }
                    }
                    if (b > n) break;
                }
            }
            cout << "Case " << c << ": " << min << endl;
        }
    }
    return 0;
}