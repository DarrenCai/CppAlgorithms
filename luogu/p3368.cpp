/**
 * p3368 【模板】树状数组 2
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 500010
long long s[N]; int a[N],  n, m;

int lowbit(int i) {
    return i&(-i);
}

void update(int i, int k) {
    int x = i;
    while (i <= n) {
        s[i] += k;
        i += lowbit(i);
    }
}

long long sum(int i) {
    long long sum = 0;
    while (i > 0) {
        sum += s[i];
        i -= lowbit(i);
    }
    return sum;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    a[0] = 0;
    while (cin >> n >> m) {
        memset(s, 0, sizeof(s));
        for (int i=1; i<=n; ++i) {
            cin >> a[i];
            update(i, a[i] - a[i-1]);
        }
        for (int i=0; i<m; ++i) {
            short c; cin >> c;
            if (c == 1) {
                int x, y, k; cin >> x >> y >> k;
                update(x, k);
                update(y+1, -k);
            } else {
                int x; cin >> x;
                cout << sum(x) << endl;
            }
        }
    }
    return 0;
}