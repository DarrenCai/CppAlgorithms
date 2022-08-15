/**
 * UVa11495
 * 逆序数问题，可以用树状数组（BIT，Binary Indexed Tree）求解。
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 100100
int c[N], ans, n;

int lowbit(int i) {
    return i&(-i);
}

void update(int i, int k) {
    while (i <= n) {
        c[i] += k;
        i += lowbit(i);
    }
}

int query(int i) {
    int sum = 0;
    while (i > 0) {
        sum += c[i];
        i ^= lowbit(i);
    }
    return sum;
}

bool solve() {
    memset(c, ans = 0, sizeof(c));
    for (int i=0; i<n; ++i) {
        int x; cin >> x;
        ans ^= (i^query(x))&1;
        update(++x, 1);
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n && n) cout << (solve() ? "Marcelo" : "Carlos") << endl;
    return 0;
}