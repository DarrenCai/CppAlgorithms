/**
 * UVa1406
 * 整数序列
 * 知识点:线段树、树状数组
 */

#include <iostream>
#include <cstring>
using namespace std;

int c[17][65537], p[17], q[17], n;

int lowbit(int x) {
    return x&(-x);
}

void update(short i, int x) {
    while (x <= p[i]) {
        ++ c[i][x];
        x += lowbit(x);
    }
}

int query(short i, int x) {
    int sum = 0;
    while (x > 0) {
        sum += c[i][x];
        x -= lowbit(x);
    }
    return sum;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short i=0; i<17; ++i) p[i] = 1<<i, q[i] = p[i]-1;
    short kase = 0;
    while (cin>>n && n>=0) {
        memset(c, 0, sizeof(c));
        while (n--) {
            int v; cin >> v;
            for (short i=1; i<17; ++i) update(i, (v&q[i]) + 1);
        }
        char c; int t = 0; long long sum = 0;
        while (cin>>c && c!='E')
            if (c == 'Q') {
                short i; cin >> i;
                int r = t&q[i];
                if (t & p[i]) {
                    sum += query(i+1, p[i]-r) + query(i+1, p[i+1]) - query(i+1, p[i+1]-r);
                } else {
                    sum += query(i+1, p[i+1]-r) - query(i+1, p[i]-r);
                }
            } else {
                int v; cin >> v; t = (t+(v&q[16]))&q[16];
            }
        cout << "Case " << ++kase << ": " << sum << endl;
    }
    return 0;
}