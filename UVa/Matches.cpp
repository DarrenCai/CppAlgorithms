/**
 * UVa11375
 * 火柴
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define N 2001
struct num {
    int v[53], n;
    num& operator= (int x) {
        v[0] = x; n =1;
        return *this;
    }
    num& operator+= (const num& x) {
        int r = 0;
        for (int i=0; i<n; ++i)
            v[i] += (i<x.n ? x.v[i] : 0) + r, r = v[i] >= 1000000000, v[i] %= 1000000000;
        while (n < x.n)
            v[n] = x.v[n] + r, r = v[n] >= 1000000000, v[n++] %= 1000000000;
        if (r) v[n++] = 1, r = 0;
        return *this;
    }
    void print() const {
        cout << v[n-1];
        for (int i=n-2; i>=0; --i) cout << setw(9) << v[i];
        cout << endl;
    }
} d[N];
int c[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}, n;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << setfill('0');
    num t; t = 1;
    for (int i=0; i<N; ++i) d[i] = 0;
    for (int i=1; i<10; ++i) d[c[i]] += t;
    for (int i=1; i<N; ++i) for (int j=0; j<10; ++j) if (i+c[j] < N) d[i+c[j]] += d[i];
    for (int i=1; i<N; ++i) d[i] += d[i-1];
    for (int i=c[0]; i<N; ++i) d[i] += t;
    while (cin >> n) d[n].print();
    return 0;
}