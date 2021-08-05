/**
 * poj3468
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 100010
long long s1[N], s2[N]; int a[N],  n, q;

int lowbit(int i) {
    return i&(-i);
}

void update(int i, int k) {
    int x = i;
    while (i <= n) {
        s1[i] += k;
        s2[i] += k * (x-1ll);
        i += lowbit(i);
    }
}

long long sum(int i) {
    long long sum = 0, x = i;
    while (i > 0) {
        sum += x*s1[i] - s2[i];
        i -= lowbit(i);
    }
    return sum;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    a[0] = 0;
    while (cin >> n >> q) {
        memset(s1, 0, sizeof(s1));
        memset(s2, 0, sizeof(s2));
        for (int i=1; i<=n; ++i) {
            cin >> a[i];
            update(i, a[i] - a[i-1]);
        }
        for (int i=0; i<q; ++i) {
            char c; cin >> c;
            if (c == 'C') {
                int a, b, c; cin >> a >> b >> c;
                update(a, c);
                update(b+1, -c);
            } else {
                int a, b; cin >> a >> b;
                cout << sum(b) - sum(a-1) << endl;
            }
        }
    }
    return 0;
}